/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:39:18 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:39:31 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_ignore(char *eof);
char	*get_eof(char **argv);
int		get_tab(char first, char *line);
void	write_lines(char first, char *eof, int fd, t_env *env);

char	*here_doc(char *eof, char suppress, t_env *env)
{
	int		fd;

	fd = open(".heredoc_data", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (NULL);
	write_lines(suppress, eof, fd, env);
	close(fd);
	return (".heredoc_data");
}

char	*expand_here_doc(char *str, t_env *env)
{
	char	*new_content;

	new_content = expand_var(str, env, ft_strlen(str) + 1);
	free(str);
	str = ft_strdup(new_content);
	free(new_content);
	return (str);
}

void	write_lines(char suppress, char *eof, int fd, t_env *env)
{
	char	*line;
	int		tab;
	int		ignore;

	ignore = get_ignore(eof);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		tab = get_tab(suppress, line);
		if (line == NULL || (ft_strncmp(eof, line + tab,
					ft_strlen(line + tab) - 1) == 0 && *line != '\n'))
			break ;
		if (ignore == 0)
		{
			line = expand_here_doc(line, env);
		}
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

int	get_tab(char suppress, char *line)
{
	int	tab;

	if (suppress == 0)
		return (0);
	tab = 0;
	while (line[tab] == '\t')
	{
		tab++;
	}
	return (tab);
}
