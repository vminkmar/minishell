/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:19:55 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 18:35:24 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (i < len && *haystack != '\0')
	{
		while ((*needle == *haystack) && (*needle != '\0') && (i + j < len))
		{
			j++;
			needle++;
			haystack++;
		}
		if (*needle == '\0')
			return ((char *) haystack - j);
		needle = needle - j;
		haystack = haystack - j;
		j = 0;
		haystack++;
		i++;
	}
	return (NULL);
}
