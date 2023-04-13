/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checks_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:14:24 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 22:19:12 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_question_mark_utils(char *str, char *new,
			char *number, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			new[i] = str[i];
			i ++;
			while (j < size)
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

char	*change_question_mark(char *str)
{
	char	*number;
	char	*new;
	int		size;

	number = ft_itoa(g_status);
	size = ft_strlen(number);
	new = malloc(sizeof(char) * (size + ft_strlen(str) + 1));
	new = change_question_mark_utils(str, new, number, size);
	free(str);
	return (new);
}

int	check_question_mark(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (0);
		i ++;
	}
	return (1);
}

int	check_after_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{	
		if ((str[i] == '$' && str[i + 1] == '\"')
			|| (str[i] == '$' && str[i + 1] == '\''))
			return (2);
		if (str[i] == '$' && is_valid(str[i + 1]) == 1 && str[i + 1] != '?')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
