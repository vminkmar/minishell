/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:29:28 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 18:12:02 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcounter(char *str, char *strend, int c)
{
	int	words;

	words = 0;
	while (str < strend)
	{
		while (*str == c)
		{
			*str = '\0';
			str++;
		}
		if (str == strend)
			break ;
		words ++;
		while (*str != c && str < strend)
			str++;
	}
	return (words);
}

static char	**usefull(char *str, char **a, char *strend)
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

char	**ft_split(char const *s, char c)
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
	words = wordcounter(str, strend, c);
	a = malloc(sizeof(char *) * (words + 1));
	if (!a)
	{
		free(str);
		return (0);
	}
	a = usefull(str, a, strend);
	free(str);
	return (a);
}
