/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:44:03 by vminkmar          #+#    #+#             */
/*   Updated: 2022/11/15 15:02:34 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formatchar(const char *str, va_list ap)
{
	int	j;

	j = 0;
	if (str[j] == 'c')
		return (ft_print_char(va_arg(ap, int)));
	else if (str[j] == 'i' || str[j] == 'd')
		return (ft_print_number(va_arg(ap, int)));
	else if (str[j] == 'x')
		return (ft_print_hex_lower(va_arg(ap, unsigned int)));
	else if (str[j] == 'X')
		return (ft_print_hex_upper(va_arg(ap, unsigned int)));
	else if (str[j] == 'u')
		return (ft_print_unsigned(va_arg(ap, unsigned int)));
	else if (str[j] == 'p')
		return (ft_print_pointer(va_arg(ap, unsigned long long)));
	else if (str[j] == 's')
		return (ft_string(va_arg(ap, char *)));
	else if (str[j] == '%')
		return (ft_percentsign('%'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		val;

	i = 0;
	val = 0;
	va_start (ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			val += ft_formatchar(&str[i + 1], ap);
			i ++;
		}
		else
			val += ft_print_char(str[i]);
			i++;
	}
	va_end(ap);
	return (val);
}
