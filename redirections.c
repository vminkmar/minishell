/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:18:43 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/03 14:09:48 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(char *name, char mode, int fileno);

int	redirect(char *str, int fileno, char mode)
{
	int		fd;
	int		std_fd;
	char	*name;
	int		i;
	int		k;

	i = 0;
	while (str[i] == ' ')
		i++;
	k = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	name = malloc(i - k + 1);
	ft_strlcpy(name, str + k, i - k + 1);
	fd = get_fd(name, mode, fileno);
	if (fd == -1)
		return (-1);
	std_fd = dup(fileno);
	if (std_fd == -1)
		return (-1);
	if (dup2(fd, fileno) == -1)
		return (close(fd), -1);
	close(fd);
	return (std_fd);
}

int	get_fd(char *name, char mode, int fileno)
{
	int	fd;

	if (fileno == STDOUT_FILENO && mode != 'a')
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (fileno == STDOUT_FILENO)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(name, O_RDONLY | O_CREAT, 0777);
	free (name);
	return (fd);
}