/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:41:58 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 22:04:07 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((content[*i] == '$' && is_valid(content[*i + 1]) == 0)
			|| (content[*i] == '$' && content[*i + 1] == '?'))
			flag = 1;
		(*i)++;
	}
	if (flag == 1)
	{
		new = delete_var(new, (ft_strlen(new) - ft_strlen(new_content)));
		new_content = expand_var(&content[*j + 1], env, *i - 1 - *j);
		new = sl_strjoin(new, new_content);
	}
	content = ft_strdup(new);
	return ((*i)++, free(new), free(new_content), content);
}

int	expand_variables_unquoted_utils(char *content, int *i, int flag)
{
	if ((content[*i] == '$' && content[*i + 1] == '\"')
		|| (content[*i] == '$' && content[*i + 1] == '\''))
	{
		(*i) += 2;
		if (content[*i - 1] == '\'')
			while (content[*i] != '\'' && content[*i] != '\0')
				(*i)++;
		else
			while (content[*i] != '\"' && content[*i] != '\0')
				(*i)++;
		flag = 1;
	}
	else
	{	
		if (content[*i] == '$')
		{
			(*i)++;
			if (content[*i] == '?')
				(*i)++;
		}		
		while (content[*i] != '\0' && is_valid(content[*i]) == 0)
			(*i)++;
	}
	return (flag);
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
	flag = expand_variables_unquoted_utils(content, i, flag);
	new_content = expand_var(&content[*j], env, *i - *j);
	new_token = sl_strjoin(new_token, new_content);
	content = ft_strdup(new_token);
	free(new_token);
	free(new_content);
	if (flag == 1)
		(*i)++;
	return (content);
}