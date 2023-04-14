/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:27:47 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 19:35:30 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}	
	while (i > -1)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s--;
		i--;
	}	
	return (0);
}	
