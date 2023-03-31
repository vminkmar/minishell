/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:50:51 by vminkmar          #+#    #+#             */
/*   Updated: 2022/11/10 15:53:43 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*values(int i, int k, unsigned int n, char *a)
{
	while (i > 0)
	{
			a[--i] = n % 10 + '0';
			n = n / 10;
	}
	a[k] = '\0';
	return (a);
}

static int	numbers(unsigned int j)
{
	int	i;

	i = 1;
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

char	*ft_unsigned(unsigned int n)
{
	char	*a;
	int		i;

	if (n > 4294967295 || n < 0)
		return (0);
	i = numbers(n);
	a = malloc(sizeof(char) * (i + 1));
	if (a == NULL)
		return (NULL);
	a = values(i, i, n, a);
	return (a);
}

int	ft_print_unsigned(unsigned int n)
{
	int		i;
	char	*j;
	size_t	c;

	j = ft_unsigned(n);
	if (j == 0)
		return (0);
	c = ft_strlen(j);
	if (c == 0)
		return (0);
	i = 0;
	while (j[i])
	{
		write(1, &j[i], 1);
		i++;
	}
	free (j);
	return (c);
}
