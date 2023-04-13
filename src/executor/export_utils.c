/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:30:56 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 00:34:50 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if ((str[i] < 'a' && str[i] > 'z') && (str[i] < 'A' && str[i] > 'Z')
		&& str[i] != '_')
		return (1);
	i = 1;
	while (str[i] != '\0')
	{
		if ((str[i] < 'a' && str[i] > 'z') || (str[i] < 'a' && str[i] > 'z')
			|| (str[i] < '0' && str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z'))
		{
			if (str[0] != '_')
				return (1);
		}
		if ((str[i] < 'A' && str[i] > 'Z') && (str[i] < 'a' && str[i] > 'z')
			&& str[i] != '_' && (str[i] < '0' && str[i] > '9'))
			return (1);
		i ++;
	}
	return (0);
}

int	check_before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '=')
			return (1);
		if (str[i] == '=' && str[i + 1] == '\0')
		{
			return (2);
		}
		i ++;
	}
	return (0);
}

int	check_first_sign(char *str)
{
	if ((str[0] < 'a' && str[0] > 'z') && (str[0] < 'A' && str[0] > 'Z')
		&& (str[0] != '_'))
		return (1);
	return (0);
}
