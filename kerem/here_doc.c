/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:16:54 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/23 06:12:38 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kerem.h"

int		get_ignore(char *eof);
char	*get_eof(char **argv);
int		get_tab(char first, char *line);
void	write_lines(char first, char *eof, int fd);

// Get as argument the String after '<<'.
// This function will return a fd to the text before EOF;
char	*here_doc(char *str)
{
	char	**argv;
	char	*eof;
	int		fd;

	argv = ft_split(str, ' ');
	if ((argv[0][0] != '-' && argv[1] != NULL)
		|| (argv[0][0] == '-' && argv[2] != NULL))
		return (NULL);
	eof = get_eof(argv);
	fd = open(".heredoc_data", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (NULL);
	write_lines(argv[0][0], eof, fd);
	return (".heredoc_data");
}

void	write_lines(char first, char *eof, int fd)
{
	char	*line;
	int		tab;
	// char	ignore;

	// ignore = get_ignore(eof);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		tab = get_tab(first, line);
		if (line == NULL || ft_strncmp(eof, line + tab
				, ft_strlen(line + tab) - 1) == 0)
			break ;
		// if (ignore == 0) {expand variables}
		write (fd, line + tab, ft_strlen(line + tab));
		free(line);
	}
	if (line != NULL)
		free(line);
}

int	get_ignore(char *eof)
{
	if ((*eof == '\'' && eof[ft_strlen(eof) - 1] == '\'')
		|| (*eof == '\"' && eof[ft_strlen(eof) - 1] == '\"') || *eof == '\\')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*get_eof(char **argv)
{
	if (argv[0][0] == '-')
		return (argv[1]);
	else
		return (argv[0]);
}

int	get_tab(char first, char *line)
{
	int	tab;

	if (first != '-')
		return (0);
	tab = 0;
	while (line[tab] == '\t')
	{
		tab++;
	}
	return (tab);
}
