/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:15:19 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/22 17:55:14 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	if (n == 0)
		return (0);
	while ((*s1 == *s2) && (*s1 != '\0') && (i < n))
	{
		if (i == n - 1)
			break ;
		s2++;
		s1++;
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
