/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:17:48 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 14:50:58 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_cmd *cmd, t_env *node, t_execute *exec, char **env)
{
	exec->pipe_num = 0;
	exec->tmp_fd = dup(STDIN_FILENO);
	exec->pids = malloc(sizeof(pid_t) * (exec->pipes + 1));
	while (exec->pipe_num < exec->pipes + 1)
	{
		checking_redirections(cmd, exec, exec->pipe_num, node);
		pipe(exec->pipes_fd);
		if (exec->pipe_num == exec->pipes)
			execute_last(exec, env, node, cmd);
		else
			execute(exec, env, node, cmd);
		exec->pipe_num++;
	}
	wait_all(exec);
	// free(exec->pids);
	return (0);
}

void	execute_last_utils(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	int	counter;

	counter = 0;
	if (exec->out != STDOUT_FILENO)
	{
		dup2(exec->out, STDOUT_FILENO);
		close(exec->out);
	}
	if (exec->in != STDIN_FILENO)
		dup2(exec->in, STDIN_FILENO);
	else
		dup2(exec->tmp_fd, STDIN_FILENO);
	while (counter < exec->pipe_num && cmd != NULL)
	{
		cmd = cmd->next;
		counter ++;
	}
	if (look_out_for_command(cmd) == 0)
		compare_cmd(cmd, node);
	else
		ft_exec(exec->commands[exec->pipe_num], env, node);
	exit(1);
}

int	execute_last(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_last_utils(exec, env, node, cmd);
	}
	else
	{
		exec->pids[exec->pipe_num] = pid;
		fbindere_close(exec->pipes_fd[1], exec->pipes_fd[0],
			exec->tmp_fd, exec->out > 2);
	}
	return (0);
}

void	execute_utils(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	int	counter;

	counter = 0;
	if (exec->out != STDOUT_FILENO)
	{
		dup2(exec->out, STDOUT_FILENO);
		close(exec->out);
	}
	else
		dup2(exec->pipes_fd[1], STDOUT_FILENO);
	if (exec->in != STDIN_FILENO)
		dup2(exec->in, STDIN_FILENO);
	else
		dup2(exec->tmp_fd, STDIN_FILENO);
	signal_handler_and_closer(exec);
	while (counter < exec->pipe_num && cmd != NULL)
	{
		cmd = cmd->next;
		counter ++;
	}
	if (look_out_for_command(cmd) == 0)
		compare_cmd(cmd, node);
	else
		ft_exec(exec->commands[exec->pipe_num], env, node);
	exit(1);
}

int	execute(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_utils(exec, env, node, cmd);
	}
	else
	{
		exec->pids[exec->pipe_num] = pid;
		fbindere_close(exec->pipes_fd[1], exec->tmp_fd, exec->out, 0);
		exec->tmp_fd = dup(exec->pipes_fd[0]);
		close(exec->pipes_fd[0]);
	}
	return (0);
}
