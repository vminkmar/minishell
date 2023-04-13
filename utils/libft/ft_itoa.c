/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:36:15 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 18:10:15 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*neg_values(int i, int k, int n, char *a)
{
	while (i > 0)
	{
		a[i--] = (n % 10) + '0';
		n = n / 10;
	}
	a[k + 1] = '\0';
	return (a);
}

static char	*pos_values(int i, int k, int n, char *a)
{
	while (i > 0)
	{
			a[--i] = n % 10 + '0';
			n = n / 10;
	}
	a[k] = '\0';
	return (a);
}

static int	numbers(int j)
{
	int	i;

	i = 1;
	if (j < 0)
		j *= -1;
	while (j != 0)
	{
		if (j >= 10)
		{
			j = j / 10;
			i++;
		}
		if (j < 10)
			break ;
	}
	return (i);
}	

char	*ft_itoa(int n)
{
	char	*a;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = numbers(n);
	if (n < 0)
	{
		a = malloc(sizeof(char) * (i + 2));
		if (a == NULL)
			return (NULL);
		a[0] = '-';
		n *= -1;
		a = neg_values(i, i, n, a);
	}
	else
	{
		a = malloc(sizeof(char) * (i + 1));
		if (a == NULL)
			return (NULL);
		a = pos_values(i, i, n, a);
	}
	return (a);
}
