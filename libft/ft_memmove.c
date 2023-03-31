/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:29:06 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/21 11:13:39 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	a = (char *)src;
	b = (char *)dst;
	i = 0;
	if (!a && !b)
		return (0);
	if (b > a)
	{
		while (len > 0)
		{
			len--;
			b[len] = a[len];
		}
	}	
	while (i < len)
	{
		b[i] = a[i];
		i++;
	}
	return (b);
}
