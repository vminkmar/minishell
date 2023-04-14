/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:38:42 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/22 15:22:08 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	c;
	size_t	d;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	c = ft_strlen(s1);
	d = ft_strlen(s2);
	a = malloc((c + d) * sizeof(char) + 1);
	if (a == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		*a = *s1;
		a++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*a = *s2;
		a++;
		s2++;
	}
	*a = '\0';
	return ((char *)a - c - d);
}
