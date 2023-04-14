/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_upper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:02:39 by vminkmar          #+#    #+#             */
/*   Updated: 2022/12/15 11:59:27 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*values(int i, int k, unsigned int n, char *a)
{
	i = i - 1;
	while (i >= 0)
	{
		if (n % 16 >= 10 && n % 16 <= 15)
			a[i--] = (n % 16) + 55;
		else
			a[i--] = (n % 16) + '0';
		n = n / 16;
	}
	a[k] = '\0';
	return (a);
}

static int	numbers(unsigned int j)
{
	int	i;

	i = 1;
	if (j < 0)
		j *= -1;
	while (j != 0)
	{
		if (j >= 16)
		{
			j = j / 16;
			i++;
		}
		if (j < 16)
			break ;
	}
	return (i);
}

char	*ft_hex_upper(unsigned int n)
{
	char	*a;
	int		i;

	i = numbers(n);
	a = malloc(sizeof(char) * (i + 1));
	if (a == NULL)
		return (NULL);
	a = values(i, i, n, a);
	return (a);
}

int	ft_print_hex_upper(unsigned int n)
{
	int		i;
	char	*j;
	size_t	c;

	j = ft_hex_upper(n);
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
