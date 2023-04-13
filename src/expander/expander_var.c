/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:23:21 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 21:00:48 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	value = get_words(str, length, counter, &sup);
	str = change_value(value, env, i, j);
	return (str);
}
