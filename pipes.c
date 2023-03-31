/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:17:48 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/31 20:08:25 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_cmd *cmd, t_env *node, t_execute exec, char **env)
{
	exec.pipe_num = 0;
	exec.tmp_fd = dup(exec.in);
	while (exec.pipe_num < exec.pipes)
	{
		pipe(exec.pipes_fd);
		if (execute(&exec, env, node, cmd) == -1)
			return (-1);
		exec.pipe_num++;
	}
	if (execute_last(&exec, env, node, cmd) == -1)
		return (-1);
	return (0);
}

int	execute_without_pipes(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;
	int		counter;
	int		status;

	counter = 0;
	pid = fork();
	if (pid == 0)
	{
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
		waitpid(pid, &status, 0);
		if(WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		if(WIFSIGNALED(status))
			g_status = WTERMSIG(status) + 128;	
	}
	return (0);
}

int	execute_last(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;
	int		counter;
	int		status;

	counter = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(exec->tmp_fd, STDIN_FILENO);
		close(exec->tmp_fd);
		if (exec->out != STDOUT_FILENO)
		{
			printf("last: %d, %d\n", exec->in, exec->out);
			dup2(exec->out, STDOUT_FILENO);
			close(exec->out);
		}
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
		waitpid(pid, &status, 0);
		if(WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		if(WIFSIGNALED(status))
			g_status = WTERMSIG(status) + 128;	
		close(exec->tmp_fd);
		if (exec->out != STDOUT_FILENO)
			close(exec->out);
	}
	return (0);
}


int	execute(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;
	int		counter;

	counter = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(exec->pipes_fd[1], STDOUT_FILENO);
		close(exec->pipes_fd[0]);
		close(exec->pipes_fd[1]);
		dup2(exec->tmp_fd, STDIN_FILENO);
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
		close(exec->pipes_fd[1]);
		close(exec->tmp_fd);
		exec->tmp_fd = exec->pipes_fd[0];
	}
	return (0);
}