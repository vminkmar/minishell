/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:28:52 by vminkmar          #+#    #+#             */
/*   Updated: 2023/01/12 14:02:34 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

int		write_to_line(char *buf, char *line, char *a, int *line_counter);
int		static_to_line(char *a, char *line, int *line_counter);
char	*extend_line(char **line);
char	*read_line(char *buf, char *line, char *a, int fd);
char	*get_next_line(int fd);
size_t	stringlen(char *str);
char	*stringmove(char *a, int i);

char	*get_next_line_loop(char *a, char *line, int *line_counter, int fd);

#endif