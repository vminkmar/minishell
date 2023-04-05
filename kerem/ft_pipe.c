/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:04:26 by kisikogl          #+#    #+#             */
/*   Updated: 2023/04/04 21:47:09 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		swap_pipes();

int	ft_pipe(t_cmd *cmd, t_env *node, t_execute exec, char **env)
{
	int	fd_out;
	int	fd_in;

	exec.pipe_num = 0;
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
		swap_pipes(exec.pipe_num == exec.pipes);
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

int	execute(t_execute exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;
	int		counter;

	counter = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		while(counter < exec.pipe_num && cmd != NULL)
		{
			cmd = cmd->next;
			counter ++;
		}
		if(look_out_for_command(cmd) == 0)
		{
			compare_cmd(cmd, node);
		}
		else
		{
			ft_exec(exec.commands[exec.pipe_num], env);
		}
		exit(1);
	}
	else
	{
		wait(NULL);
	}

	return (0);
}

int	swap_pipes(int last)
{
	int static	which = 0;

	if (last == 1)
	{
		which = 0;
		return (0);
	}
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
