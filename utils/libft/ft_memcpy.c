/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:50:36 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/22 11:23:04 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pa;
	unsigned char	*pb;

	i = 0;
	pa = (unsigned char *) src;
	pb = (unsigned char *) dest;
	if (pa == NULL && pb == NULL)
		return (NULL);
	while (i < n)
	{
		pb[i] = pa[i];
		i++;
	}
	return (pb);
}
