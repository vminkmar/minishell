/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:17:48 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 16:07:51 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void wait_all(t_execute *exec)
{
	int counter;
	int status;

	counter = 0;
	while(counter < exec->pipe_num + 1)
	{
		waitpid(exec->pids[counter], &status, 0);
		counter ++;
	}
	if(WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if(WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}


int	ft_pipe(t_cmd *cmd, t_env *node, t_execute *exec, char **env)
{
	exec->pipe_num = 0;
	exec->tmp_fd = dup(STDIN_FILENO);
	exec->pids = malloc(sizeof(pid_t) * (exec->pipes + 1));
	while (exec->pipe_num < exec->pipes + 1)
	{
		checking_redirections(cmd, exec, exec->pipe_num);
		pipe(exec->pipes_fd);
		if (exec->pipe_num == exec->pipes)
			execute_last(exec, env, node, cmd);	
		else
			execute(exec, env, node, cmd);
		exec->pipe_num++;
	}
	wait_all(exec);

	return (0);
}

int	execute_last(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;
	int counter;
	
	counter = 0;
	pid = fork();
	if (pid == 0)
	{
		if (exec->out != STDOUT_FILENO)
		{
			dup2(exec->out, STDOUT_FILENO);
			close(exec->out);
		}
		if (exec->in != STDIN_FILENO)
		{
			dup2(exec->in, STDIN_FILENO);
		}
		else
			dup2(exec->tmp_fd, STDIN_FILENO);
		close(exec->pipes_fd[0]);
		close(exec->pipes_fd[1]);
		close(exec->tmp_fd);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		while(counter < exec->pipe_num && cmd != NULL)
		{
			cmd = cmd->next;
			counter ++;
		}
		if(look_out_for_command(cmd) == 0)
			compare_cmd(cmd, node);
		else
			ft_exec(exec->commands[exec->pipe_num], env, node);
		exit(1);
	}
	else
	{
		if (exec->pipes_fd[1] > 2)
			close(exec->pipes_fd[1]);
		if (exec->pipes_fd[0] > 2)
			close(exec->pipes_fd[0]);
		if (exec->tmp_fd > 2)
			close(exec->tmp_fd);
		if (exec->out > 2)
			close(exec->out);
	}
	return (0);
}

int	execute(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;

	int counter;

	counter = 0;
	pid = fork();
	if (pid == 0)
	{
		if (exec->out != STDOUT_FILENO)
		{
			dup2(exec->out, STDOUT_FILENO);
			close(exec->out);
		}
		else
			dup2(exec->pipes_fd[1], STDOUT_FILENO);
		if(exec->in != STDIN_FILENO)
			dup2(exec->in, STDIN_FILENO);
		else
			dup2(exec->tmp_fd, STDIN_FILENO);
		close(exec->pipes_fd[0]);
		close(exec->pipes_fd[1]);
		close(exec->tmp_fd);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		while(counter < exec->pipe_num && cmd != NULL)
		{
			cmd = cmd->next;
			counter ++;
		}
		if(look_out_for_command(cmd) == 0)
			compare_cmd(cmd, node);
		else
			ft_exec(exec->commands[exec->pipe_num], env, node);
		exit(1);
	}
	else
	{
		exec->pids[exec->pipe_num] = pid;
		if (exec->pipes_fd[1] > 2)
			close(exec->pipes_fd[1]);
		if (exec->tmp_fd > 2)
			close(exec->tmp_fd);
		if (exec->out > 2)
			close(exec->out);
		exec->tmp_fd = dup(exec->pipes_fd[0]);
		close(exec->pipes_fd[0]);
	}
	return (0);
}

