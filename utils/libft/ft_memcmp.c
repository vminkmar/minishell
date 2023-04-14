/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:41:45 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/22 11:23:35 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*pa;
	unsigned char	*pb;
	size_t			i;

	i = 0;
	pa = (unsigned char *)s1;
	pb = (unsigned char *)s2;
	if (n == 0)
		return (0);
	if (pa == NULL && pb == NULL)
		return (0);
	while ((pa[i] == pb[i]) && (i < n - 1))
	{
		i++;
	}
	return (pa[i] - pb[i]);
}
