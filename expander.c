/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:37:04 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/04 11:52:17 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *value, char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 0;
	dest = malloc(ft_strlen(str) + ft_strlen(value) + 1);
	if (dest == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	j = 0;
	while (str[i] != '\0')
	{
		dest[j] = str[i];
		if (str[i] == '$')
		{	
			i++;
			while (is_valid(str[i]) == 0)
			{
				dest[j] = str[i];
				j++;
				i++;
			}
		}
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*remove_variable(char *str)
{
	char	*dest;
	int		j;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(str) + 1);
	if (dest == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{	
			i++;
		}
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*remove_dollar(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*new;

	flag = 0;
	new = malloc(ft_strlen(str));
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && flag == 0)
		{
			flag = 1;
			i++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free (str);
	return (new);
}

int	get_lenght_var(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i ++;
			while (is_valid(str[i]) == 0)
			{
				i ++;
				counter ++;
			}
			return (counter);
		}
		i ++;
	}
	return (counter);
}

char	*delete_var(char *content, int length)
{
	char	*string;
	int		i;

	i = 0;
	string = malloc(length + 1);
	while (i < length)
	{
		string[i] = content[i];
		i ++;
	}
	string[i] = '\0';
	return (string);
}

char	*expand_variables_quoted(char *content, t_env *env, int *i, int *j)
{
	char	*new_content;
	char	*new;
	int		flag;

	flag = 0;
	new_content = NULL;
	new = ft_strdup("");
	new_content = remove_dq(content, i);
	new = sl_strjoin(new, new_content);
	*i = *j + 1;
	while (content[*i] != '\"' && content[*i] != '\0')
	{
		if (content[*i] == '$' && is_valid(content[*i + 1]) == 0)
			flag = 1;
		(*i)++;
	}
	if (flag == 1)
	{
		new = delete_var(new, (ft_strlen(new) - ft_strlen(new_content)));
		new_content = expand_var(&content[*j + 1], env, *i - 1 - *j);
		new = sl_strjoin(new, new_content);
	}
	(*i)++;
	content = ft_strdup(new);
	return (free(new), free(new_content), content);
}

char	*expand_variables_unquoted(char *content, t_env *env, int *i, int *j)
{
	char	*new_content;
	char	*new_token;
	int		flag;

	flag = 0;
	new_content = NULL;
	new_token = ft_strdup("");
	*j = *i;
	if((content[*i] == '$' && content[*i + 1] == '\"') || (content[*i] == '$' && content[*i + 1] == '\''))
	{
		(*i) += 2;
		if(content[*i - 1] == '\'')
		{
			while(content[*i] != '\'' && content[*i] != '\0')
				(*i)++;
		}
		else
		{
			while(content[*i] != '\"' && content[*i] != '\0')
				(*i)++;
		}
		flag = 1;
	}
	else
	{	if(content[*i] == '$')
		{
			(*i)++;
			if(content[*i] == '?')
				(*i)++;
		}		
		while (content[*i] != '\0' && is_valid(content[*i]) == 0)
			(*i)++;
	}
	new_content = expand_var(&content[*j], env, *i - *j);
	new_token = sl_strjoin(new_token, new_content);
	content = ft_strdup(new_token);
	free(new_token);
	free(new_content);
	if (flag == 1)
		(*i)++;
	return (content);
}

char	*expand_sq(char *content, int *i, int *j)
{
	char	*new_content;
	char	*new_token;

	new_content = NULL;
	new_token = ft_strdup("");
	*j = *i;
	new_content = remove_sq(content, i);
	new_token = sl_strjoin(new_token, new_content);
	(*i)++;
	content = ft_strdup(new_token);
	free(new_token);
	free(new_content);
	return (content);
}

char	*expand_rest(char *content, int *i, int *j)
{
	char	*new_content;
	char	*new_token;

	new_content = NULL;
	new_token = ft_strdup("");
	*j = *i;
	while (content[*i] != '\'' && content[*i] != '\"' && content[*i] != '\0'
		&& content[*i] != '$')
		(*i)++;
	new_content = ft_substr(content, *j, *i - *j);
	new_token = sl_strjoin(new_token, new_content);
	content = ft_strdup(new_token);
	free(new_token);
	free(new_content);
	return (content);
}

char	*expand_variables(char *content, t_env *env)
{
	int		i;
	int		j;
	char	*new_token;

	i = 0;
	j = 0;
	new_token = ft_strdup("");
	while (content[i] != '\0')
	{
		if (content[i] == '\"')
		{
			j = i;
			new_token = sl_strjoin(new_token,
					expand_variables_quoted(content, env, &i, &j));
		}
		if (content[i] == '\'')
			new_token = sl_strjoin(new_token, expand_sq(content, &i, &j));
		if (content[i] == '$')
			new_token = sl_strjoin(new_token,
					expand_variables_unquoted(content, env, &i, &j));
		if (content[i] != '\'' && content[i] != '\"' && content[i] != '\0')
			new_token = sl_strjoin(new_token, expand_rest(content, &i, &j));
	}
	return (new_token);
}

int	expander(t_cmd *cmd, t_env *env)
{
	t_token	*token;

	while (cmd)
	{
		token = cmd->head;
		while(token != NULL)
		{	
			token->content = expand_variables(token->content, env);
			token = token->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
