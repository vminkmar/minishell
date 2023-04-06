/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:05:19 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 20:31:00 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_in_get_value(char *dest, char *str)
{
	int		i;
	int		j;

	i = 0;
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

char	*get_value(char *value, char *str)
{
	char	*dest;

	dest = malloc(ft_strlen(str) + ft_strlen(value) + 1);
	if (dest == NULL)
	{	
		printf("memory allocation failed");
		return (NULL);
	}
	copy_in_get_value(dest, str);
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
