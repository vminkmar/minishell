/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:27:36 by vminkmar          #+#    #+#             */
/*   Updated: 2022/11/15 16:49:51 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*stringmove(char *a, int i)
{
	int	j;

	j = 0;
	while (i < BUFFER_SIZE && a[i + 1] != '\0')
	{
		a[j] = a[i + 1];
		i++;
		j++;
	}
	a[j] = '\0';
	return (a);
}

static char	*string_cpy_length(char *dest, const char *src, size_t start,
size_t end)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + start < end)
	{
		dest[i + start] = src[i];
		i++;
	}
	dest[i + start] = '\0';
	return (dest);
}

static char	*string_cpy_length2(char *dest, const char *src, size_t start,
size_t end)
{
	size_t	i;

	i = 0;
	while (src[i + start] != '\0' && i + start < end)
	{
		dest[i] = src[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	static_to_line(char *a, char *line, int *line_counter)
{
	int	i;

	i = 0;
	while (a[i] != '\n' && a[i] != '\0' && i < BUFFER_SIZE)
	{
		(*line_counter)++;
		i++;
	}
	if (i < BUFFER_SIZE && a[i] == '\n')
	{
		string_cpy_length(line, a, 0, i + 1);
		stringmove(a, i);
		return (1);
	}
	string_cpy_length(line, a, 0, i);
	a[0] = '\0';
	return (0);
}

int	write_to_line(char *buf, char *line, char *a, int *line_counter)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0' && i < BUFFER_SIZE)
	{
		(*line_counter)++;
		i++;
	}
	if (buf[i] == '\n')
	{
		(*line_counter)++;
		i++;
	}
	string_cpy_length(line, buf, *line_counter - i, *line_counter);
	if (i == BUFFER_SIZE && buf[BUFFER_SIZE - 1] == '\n')
		return (1);
	if (i < BUFFER_SIZE)
	{
		string_cpy_length2(a, buf, i, BUFFER_SIZE);
		return (1);
	}
	return (0);
}
