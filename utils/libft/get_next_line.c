/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:53:55 by vminkmar          #+#    #+#             */
/*   Updated: 2023/01/08 14:57:01 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	stringlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*stringcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*extend_line(char **line)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (stringlen(*line) + BUFFER_SIZE + 1));
	if (new_line == NULL)
		return (NULL);
	stringcpy(new_line, *line, stringlen(*line));
	free(*line);
	*line = new_line;
	return (*line);
}

char	*get_next_line_loop(char *a, char *line, int *line_counter, int fd)
{
	int		bytes;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		bytes = read (fd, buf, BUFFER_SIZE);
		if (bytes < 0 || (bytes == 0 && *line_counter == 0))
		{
			free(buf);
			free(line);
			return (NULL);
		}
		buf[bytes] = '\0';
		if (bytes == 0)
			break ;
		if (write_to_line(buf, line, a, line_counter) == 0)
			extend_line(&line);
		else
			break ;
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			line_counter;
	static char	a[BUFFER_SIZE];

	line_counter = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (line == NULL)
		return (NULL);
	if (*a != '\0')
	{
		if (static_to_line(a, line, &line_counter) == 1)
			return (line);
		else
			extend_line(&line);
	}
	line = get_next_line_loop(a, line, &line_counter, fd);
	return (line);
}
