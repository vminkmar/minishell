/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:49:56 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 19:45:42 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*a;

	if (count != 0 && size > (SIZE_MAX / count))
		return (0);
	a = malloc(count * size);
	if (!a)
		return (0);
	ft_bzero(a, count * size);
	return (a);
}
