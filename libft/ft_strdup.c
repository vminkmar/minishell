/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:37:13 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/22 11:32:00 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;
	int		j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
		i++;
	d = malloc(i * sizeof(char) + 1);
	if (d == NULL)
		return (NULL);
	while (j <= i)
	{
		d[j] = s[j];
		j++;
	}
	return (d);
}
