/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:46:57 by vminkmar          #+#    #+#             */
/*   Updated: 2022/11/04 12:55:58 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		ft_print_char(char c);
int		ft_string(const char *str);
int		ft_print_number(int n);
int		ft_percentsign(char a);
int		ft_print_hex_lower(unsigned int n);
int		ft_print_hex_upper(unsigned int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_pointer(unsigned long long n);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif
