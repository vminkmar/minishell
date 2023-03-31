/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:11:24 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 19:47:58 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pa;
	size_t			i;

	pa = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		pa[i] = c;
		i ++;
	}
	return (pa);
}
