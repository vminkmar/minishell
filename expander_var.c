/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:23:21 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/03 18:16:41 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *change_question_mark(char *str)
{
	int	i;
	int	j;
	char *number;
	char *new;
	int size;

	number = ft_itoa(g_status);
	size = ft_strlen(number);
	new = malloc(sizeof(char) * (size + ft_strlen(str) + 1));
	i = 0;
	j = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '$' && str[i + 1] == '?')
		{
			new[i] = str[i];
			i ++;
			while(j < size)
			{
				new[i] = number[j];
				j ++;
				i ++;
			}
		}
		else
			new[i] = str[i];
		i ++;
	}
	new[i] = '\0';
	return (new);
}

int check_question_mark(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '$' && str[i + 1] == '?')
			return (0);
		i ++;
	}
	return (1);
}
int check_after_dollar(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{	
		if ((str[i] == '$' && str[i + 1] == '\"') || (str[i] == '$' && str[i + 1] == '\''))
			return (2);
		if (str[i] == '$' && is_valid(str[i + 1]) == 1 && str[i + 1] != '?')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
char	*change_value_util(char **str, t_env *env, int *i)
{
	int		flag;
	char	*dollar;
	t_env	*node;
	int		j;
	int		k;

	j = 0;
	flag = 0;
	node = env;
	if (check_after_dollar(str[*i]) == 2)
	{
		str[*i] = remove_dollar(str[*i]);
		k = ft_strlen(str[*i]);
		if (str[*i][0] == '\'')
			str[*i] = expand_sq(str[*i], &j, &k);
		if (str[*i][0] == '\"')
			str[*i] = remove_dq(str[*i], &j);
		return(str[*i]);
	}	
	if (check_after_dollar(str[*i]) == 1)
		return(str[*i]);
	dollar = malloc(ft_strlen(str[*i]));
	if(check_question_mark(str[*i]) == 0)
	{
		dollar = change_question_mark(str[*i]);
		dollar = remove_dollar(dollar);
		str[*i] = ft_strdup(dollar);
		free(dollar);
		return (str[*i]);
	}
	else
		dollar = remove_dollar(str[*i]);
	while (node != NULL)
	{
		if (ft_strcmp(node->name, dollar) == 0)
		{
			flag = 1;
			str[*i] = remove_variable(node->value);
			free(dollar);
			break ;
		}
		node = node->next;
	}
	if (flag == 0)
	{
		str[*i] = ft_strdup("");
	}
	return (str[*i]);
}

char	*change_value(char **str, t_env *env, int i, int j)
{
	char	*new;

	new = ft_strdup("");
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$')
			{
				change_value_util(str, env, &i);
			}
			j++;
		}
		new = sl_strjoin(new, str[i]);
		i++;
	}
	return (new);
}

char	**get_words(char *str, char **value, int length)
{
	int	i;
	int	j;
	int	words;

	words = 0;
	i = 0;
	j = 0;
	while (i < length)
	{
		if((str[i] == '$' && str[i + 1] == '\"') || (str[i] == '$' && str[i + 1] == '\''))
		{
			j = i;
			i += 2;
			if(str[i - 1] == '\'')
			{
				while(str[i] != '\'' && str[i] != '\0')
					(i)++;
			}
			else
			{
				while(str[i] != '\"' && str[i] != '\0')
					(i)++;
			}
			value[words] = ft_substr(str, j, i + 1 - j);
			words ++;
			j = i;
		}
		if (str[i] == '$' && str[i + 1] == '?')
		{
			j = i;
			i += 2;
			while (is_valid(str[i]) == 0 && i < length)
				i++;
			value[words] = ft_substr(str, j, i - j);
			words ++;
			j = i;
		}
		if (str[i] == '$')
		{
			j = i;
			i ++;
			while (is_valid(str[i]) == 0 && i < length)
				i++;
			value[words] = ft_substr(str, j, i - j);
			words ++;
			j = i;
		}
		while (str[i] != '$' && i < length)
		{
			if (str[i + 1] == '$')
			{
				value[words] = ft_substr(str, j, i + 1 - j);
				j = i;
				words ++;
			}
			else if (i + 1 == length)
			{
				value[words] = ft_substr(str, j, i + 1 - j);
				j = i;
				words ++;
			}
			i++;
		}
	}
	value[words] = NULL;
	return (value);
}

int	get_number(char *str, int length)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (i < length)
	{
		if((str[i] == '$' && str[i + 1] == '\"') || (str[i] == '$' && str[i + 1] == '\''))
		{
			(i) += 2;
			if(str[i - 1] == '\'')
			{
				while(str[i] != '\'' && str[i] != '\0')
					(i)++;
			}
			else
			{
				while(str[i] != '\"' && str[i] != '\0')
					(i)++;
			}
			counter ++;
			(i)--;
		}
		else if(str[i] == '$' && str[i + 1] == '?')
		{
			counter ++;
			i = i + 2;
		}
		else if (str[i] == '$')
		{
			i ++;
			while (is_valid(str[i]) == 0)
				i++;
			counter++;
		}
		while (str[i] != '$' && i < length)
		{
			if (str[i + 1] == '$')
				counter ++;
			if (str[i + 1] == '\0')
				counter ++;
			i++;
		}
	}
	return (counter);
}

char	*expand_var(char *str, t_env *env, int length)
{
	int		counter;
	char	**value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	counter = get_number(str, length);
	value = malloc((counter + 1) * sizeof(char *));
	if (value == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	value = get_words(str, value, length);
	str = change_value(value, env, i, j);
	free(value);
	return (str);
}
