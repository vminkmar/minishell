/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:20:29 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/22 11:42:22 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dq(char *str, int *i)
{
	char	*dest;
	int		j;

	dest = malloc(ft_strlen(str) + 1);
	if (dest == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	j = 0;
	if (str[*i] == '\"')
	{	
		(*i)++;
	}
	while (str[*i] != '\"' && str[*i] != '\0')
	{
			dest[j] = str[*i];
			(*i)++;
			j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*remove_sq(char *str, int *i)
{
	char	*dest;
	int		j;

	dest = malloc(ft_strlen(str) + 1);
	if (dest == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	j = 0;
	if (str[*i] == '\'')
	{	
		(*i)++;
	}
	while (str[*i] != '\'' && str[*i] != '\0')
	{
			dest[j] = str[*i];
			(*i)++;
			j++;
	}
	dest[j] = '\0';
	return (dest);
}
