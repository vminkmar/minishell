/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:18:43 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/04 22:40:40 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(char *name, char mode, int fileno);

int	redirect(char *str, int fileno, char mode)
{
	int		fd;

	fd = get_fd(str, mode, fileno);
	if (fd == -1)
		return (-1);
	return (fd);
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
	return (fd);
}