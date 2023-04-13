/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:37:03 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/12 15:45:28 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)( unsigned int, char))
{
	int		i;
	char	*a;

	i = 0;
	if (s == NULL || f == NULL)
		return (0);
	a = malloc(sizeof(char) * (ft_strlen(s) +1));
	if (!a)
		return (0);
	while (s[i] != '\0')
	{
		a[i] = f(i, s[i]);
		i ++;
	}
	a[i] = '\0';
	return (a);
}
