/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:kerem/redirect.c
/*   redirect.c                                         :+:      :+:    :+:   */
=======
/*   redirections.c                                     :+:      :+:    :+:   */
>>>>>>> testtest:redirections.c
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:kerem/redirect.c
/*   Created: 2023/03/17 09:23:03 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/27 19:07:16 by kisikogl         ###   ########.fr       */
=======
/*   Created: 2023/03/24 15:18:43 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/28 20:14:14 by vminkmar         ###   ########.fr       */
>>>>>>> testtest:redirections.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(char *name, char mode, int fileno);

<<<<<<< HEAD:kerem/redirect.c
int	get_fd(char *name, char mode, int fileno);

// Get as argument the String after '>'.
// This function will change STDOUT so that it "points" to the file.
// The function will return a duplicate FD to the real STDOUT;
// The caller has to change STDOUT back to its original place by
// duplicating the returned value: dup2(returned_fd, STDOUT_FILENO).
// mode 'a' for append mode, anything else for default
=======
>>>>>>> testtest:redirections.c
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
<<<<<<< HEAD:kerem/redirect.c
}
=======
}
>>>>>>> testtest:redirections.c
