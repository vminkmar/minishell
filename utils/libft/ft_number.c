/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:05:59 by vminkmar          #+#    #+#             */
/*   Updated: 2022/11/11 10:43:01 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_number(int n)
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

int	ft_print_number(int n)
{
	int		i;
	char	*j;
	size_t	c;

	j = ft_number(n);
	c = ft_strlen(j);
	i = 0;
	if (j[i] == 0)
		return (0);
	while (j[i])
	{
		write(1, &j[i], 1);
		i++;
	}
	free (j);
	return (c);
}
