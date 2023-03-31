/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:34:36 by vminkmar          #+#    #+#             */
/*   Updated: 2022/11/10 15:52:40 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*values(int i, int k, unsigned long long n, char *a)
{	
	i = i -1;
	while (i >= 0)
	{
		if (n % 16 >= 10 && n % 16 <= 15)
			a[i--] = (n % 16) + 87;
		else
			a[i--] = (n % 16) + '0';
		n = n / 16;
	}
	a[k] = '\0';
	return (a);
}

static int	numbers(unsigned long long j)
{	
	int	i;

	i = 1;
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

char	*ft_pointer(unsigned long long c)
{
	char	*a;
	int		i;

	i = numbers(c);
	a = malloc(sizeof(char) * (i + 1));
	if (a == NULL)
		return (NULL);
	a = values(i, i, c, a);
	return (a);
}

int	ft_print_pointer(unsigned long long n)
{
	int		i;
	char	*j;
	size_t	c;

	j = ft_pointer(n);
	c = ft_strlen(j);
	i = 0;
	if (j[i] == 0)
		return (0);
	c += write(1, "0x", 2);
	while (j[i])
	{
		write(1, &j[i], 1);
		i++;
	}
	free (j);
	return (c);
}
