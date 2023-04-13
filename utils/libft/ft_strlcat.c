/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:41:30 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 18:42:35 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = ft_strlen(src);
	j = ft_strlen(dst);
	if (j >= dstsize || dstsize == 0)
		return (dstsize + k);
	while (src[i] != '\0' && (j + i) < (dstsize - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	if (dst[j + i] != '\0')
		dst[j + i] = '\0';
	if (dstsize > j)
		return (k + j);
	return (dstsize + k);
}
