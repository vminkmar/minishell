/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:04:26 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/27 19:07:19 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kerem.h"

int		execute(char **argv);
int		swap_pipes();

int	ft_pipe(char ***argv, int pipe_count)
{
	int	fd_out;
	int	fd_in;
	int	pipe_num;

	pipe_num = 0;
	if (pipe_count > 0)
		fd_in = redirect(PIPE1, STDIN_FILENO, 'n');
	fd_out = redirect(PIPE2, STDOUT_FILENO, 'n');
	while (pipe_num < pipe_count + 1)
	{
		if (pipe_num == pipe_count)
		{
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				return (close(fd_in), close(fd_out), -1);
		}

		if (execute(argv[pipe_num]) == -1)
			return (-1);
		if (pipe_num != pipe_count)
			swap_pipes();
		pipe_num++;
	}
	close(fd_out);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), -1);
	close(fd_in);
	unlink(PIPE1);
	unlink(PIPE2);
	return (0);
}

int ft_pipe(t_cmd *cmd, t_env *node, t_execute exec, char **env)
{
    int fd_out;
    int fd_in;

    exec.pipe_num = 0;
    if (exec.pipes > 0)
        fd_in = redirect(PIPE1, STDIN_FILENO, 'n');
    fd_out = redirect(PIPE2, STDOUT_FILENO, 'n');
    while (exec.pipe_num < exec.pipes + 1)
    {
        if (exec.pipe_num == exec.pipes)
        {
            if (dup2(fd_out, STDOUT_FILENO) == -1)
                return (close(fd_in), close(fd_out), -1);
        }
        if (execute(exec, env, node, cmd) == -1)
            return (-1);
        if (exec.pipe_num != exec.pipes)
            swap_pipes();
        exec.pipe_num++;
    }
    close(fd_out);
    if (dup2(fd_in, STDIN_FILENO) == -1)
        return (close(fd_in), -1);
    close(fd_in);
    unlink(PIPE1);
    unlink(PIPE2);
    return (0);
}

int	execute(char **argv)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_exec(argv);
		return (-1);
	}
	else
		wait(NULL);
	return (0);
}

int	swap_pipes()
{
	// int			fd;
	int static	which = 0;

	if (which == 0)
		which = 1;
	else
		which = 0;
	if (which == 0)
	{
		if (close(redirect(PIPE1, STDIN_FILENO, 'n')) == -1)
			return (-1);
		if (close(redirect(PIPE2, STDOUT_FILENO, 'n')) == -1)
			return (-1);
	}
	else
	{
		if (close(redirect(PIPE2, STDIN_FILENO, 'n')) == -1)
			return (-1);
		if (close(redirect(PIPE1, STDOUT_FILENO, 'n')) == -1)
			return (-1);
	}
	return (0);
}
