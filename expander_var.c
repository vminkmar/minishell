/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:23:21 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 00:06:35 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value_check_dollar(char **str, int *i)
{
	int		j;
	int		k;
	char	*dollar;

	j = 0;
	k = 0;
	if (check_after_dollar(str[*i]) == 2)
	{
		str[*i] = remove_dollar(str[*i]);
		k = ft_strlen(str[*i]);
		if (str[*i][0] == '\'')
			str[*i] = expand_sq(str[*i], &j, &k);
		if (str[*i][0] == '\"')
			str[*i] = remove_dq(str[*i], &j);
		return (0);
	}	
	if (check_after_dollar(str[*i]) == 1)
		return (0);
	dollar = malloc(ft_strlen(str[*i]));
	if (check_question_mark(str[*i]) == 0)
	{
		str[*i] = ft_strdup(remove_dollar(change_question_mark(str[*i])));
		return (free(dollar), 0);
	}
	return (1);
}

char	*change_value_util(char **str, t_env *env, int *i)
{
	int		flag;
	char	*dollar;
	t_env	*node;

	node = env;
	flag = 0;
	if (change_value_check_dollar(str, i) == 0)
		return(str[*i]);
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
		str[*i] = ft_strdup("");
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





int	get_number_util(char *str, int *i, int counter)
{
	if ((str[*i] == '$' && str[*i + 1] == '\"')
		|| (str[*i] == '$' && str[*i + 1] == '\''))
	{
		(*i) += 2;
		if (str[*i - 1] == '\'')
		{
			while (str[*i] != '\'' && str[*i] != '\0')
				(*i)++;
		}
		else
		{
			while (str[*i] != '\"' && str[*i] != '\0')
				(*i)++;
		}
		counter ++;
		(*i)--;
	}
	else if (str[*i] == '$' && str[*i + 1] == '?')
	{
		counter ++;
		*i = *i + 2;
	}
	return (counter);
}


int	get_number(char *str, int length)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (i < length)
	{
		counter += get_number_util(str, &i, 0);
		if (str[i] == '$')
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
	t_sup	sup;
	
	i = 0;
	j = 0;
	counter = get_number(str, length);
	value = malloc((counter + 1) * sizeof(char *));
	if (value == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	value = get_words(str, length, counter, &sup);
	str = change_value(value, env, i, j);
	free(value);
	return (str);
}
