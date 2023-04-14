/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:08:48 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/22 18:34:54 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_wordcounter(char *str, char *strend, int c)
{
	int	words;

	words = 1;
	while (str < strend)
	{
		if (*str == c)
		{
			*str = '\0';
			words ++;
			break ;
		}
		if (str == strend)
			break ;
		str++;
	}
	return (words);
}

static char	**new_usefull(char *str, char **a, char *strend)
{
	int	i;

	i = 0;
	while (str < strend)
	{
		while (*str == '\0' && str < strend)
			str++;
		if (str == strend)
			break ;
		a[i] = ft_strdup(str);
		if (a[i] == NULL)
		{
			i = 0;
			while (a[i] != NULL)
				free(a[i++]);
			free(a);
			return (NULL);
		}
		while (*str != '\0' && str < strend)
			str++;
		i++;
	}
	a[i] = NULL;
	return (a);
}

char	**split_env(char const *s, char c)
{
	char	*str;
	char	*strend;
	char	**a;
	int		words;
	int		i;

	if (s == 0)
		return (0);
	i = ft_strlen(s);
	str = ft_strdup(s);
	if (!str)
		return (0);
	strend = str + i;
	words = new_wordcounter(str, strend, c);
	a = malloc(sizeof(char *) * (words + 1));
	if (!a)
	{
		free(str);
		return (0);
	}
	a = new_usefull(str, a, strend);
	free(str);
	return (a);
}
