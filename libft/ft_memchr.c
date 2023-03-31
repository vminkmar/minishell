/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:44:51 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/12 16:24:34 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pa;
	unsigned char	e;
	size_t			i;

	pa = (unsigned char *)s;
	e = (unsigned char)c;
	i = 0;
	while ((i < n))
	{
		if (pa[i] == e)
		{
			return (pa + i);
		}
		i++;
	}
	return (0);
}
