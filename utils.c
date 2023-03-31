/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:09:20 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/30 16:16:04 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*d;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	d = malloc(i * sizeof(char) + 1);
	if (d == NULL)
		return (NULL);
	while (j <= i)
	{
		d[j] = s1[j];
		j++;
	}
	return (d);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	b;
	char	*a;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (*s1 != '\0' && *set != '\0')
	{
		if (!ft_strchr(set, *s1))
			break ;
		s1++;
	}
	if (*s1 == '\0')
		return (ft_strdup(""));
	b = ft_strlen(s1);
	b--;
	while (b > 0)
	{
		if (!ft_strchr(set, s1[b]))
			break ;
		b--;
	}
	a = ft_substr(s1, 0, b + 1);
	return ((char *)a);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
