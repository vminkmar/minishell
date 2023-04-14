/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:37:13 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 11:44:21 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*pnt;
	size_t	a;

	if (s1 == NULL)
		return (NULL);
	pnt = (char *)malloc(ft_strlen(s1) + 1);
	if (pnt == NULL)
		return (NULL);
	a = 0;
	while (a < ft_strlen(s1) + 1)
	{
		pnt[a] = s1[a];
		a++;
	}
	return (pnt);
}
