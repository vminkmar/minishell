/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:17:48 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/04 13:09:59 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	swap_pipes(int last);

int	ft_pipe(t_cmd *cmd, t_env *node, t_execute *exec, char **env)
{
	int	fd_out;
	int	fd_in;

	exec->pipe_num = 0;
	fd_in = redirect(PIPE1, STDIN_FILENO, 'n');
	fd_out = redirect(PIPE2, STDOUT_FILENO, 'n');
	while (exec->pipe_num < exec->pipes + 1)
	{
		checking_redirections(cmd, exec, exec->pipe_num + 1);
		if (exec->pipe_num == exec->pipes)
		{
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				return (close(fd_in), close(fd_out), -1);
		}
		if (execute(exec, env, node, cmd) == -1)
			return (-1);
		swap_pipes(exec->pipe_num == exec->pipes);
		exec->pipe_num++;
	}
	
	
	close(fd_out);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), -1);
	close(fd_in);
	unlink(PIPE1);
	unlink(PIPE2);
	return (0);
}

int	execute(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		counter;

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
		{
			compare_cmd(cmd, node);
		}
		else
		{
			ft_exec(exec->commands[exec->pipe_num], env, node);
		}
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

// int	ft_pipe(t_cmd *cmd, t_env *node, t_execute exec, char **env)
// {
// 	exec->pipe_num = 0;
// 	exec->tmp_fd = dup(exec->in);
// 	while (exec->pipe_num < exec->pipes)
// 	{
// 		// checking_redirections(cmd, &exec, exec->pipe_num + 1);
// 		pipe(exec->pipes_fd);
// 		if (execute(&exec, env, node, cmd) == -1)
// 			return (-1);
// 		exec->pipe_num++;
// 	}
// 	if (execute_last(&exec, env, node, cmd) == -1)
// 		return (-1);
// 	return (0);
// }

// int	execute_without_pipes(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
// {
// 	pid_t	pid;
// 	int		counter;
// 	int		status;

// 	counter = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, SIG_DFL);
// 		while(counter < exec->pipe_num && cmd != NULL)
// 		{
// 			cmd = cmd->next;
// 			counter ++;
// 		}
// 		if(look_out_for_command(cmd) == 0)
// 			compare_cmd(cmd, node);
// 		else
// 			ft_exec(exec->commands[exec->pipe_num], env, node);
// 		exit(1);
// 	}
// 	else
// 	{	
// 		waitpid(pid, &status, 0);
// 		if(WIFEXITED(status))
// 			g_status = WEXITSTATUS(status);
// 		if(WIFSIGNALED(status))
// 			g_status = WTERMSIG(status) + 128;
// 	}
// 	return (0);
// }

// int	execute_last(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
// {
// 	pid_t	pid;
// 	int		counter;
// 	int		status;

// 	counter = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(exec->tmp_fd, STDIN_FILENO);
// 		close(exec->tmp_fd);
// 		if (exec->out != STDOUT_FILENO)
// 		{
// 			dup2(exec->out, STDOUT_FILENO);
// 			close(exec->out);
// 		}
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, SIG_DFL);
// 		while(counter < exec->pipe_num && cmd != NULL)
// 		{
// 			cmd = cmd->next;
// 			counter ++;
// 		}
// 		if(look_out_for_command(cmd) == 0)
// 			compare_cmd(cmd, node);
// 		else
// 			ft_exec(exec->commands[exec->pipe_num], env, node);
// 		exit(1);
// 	}
// 	else
// 	{	
// 		waitpid(pid, &status, 0);
// 		if(WIFEXITED(status))
// 			g_status = WEXITSTATUS(status);
// 		if(WIFSIGNALED(status))
// 			g_status = WTERMSIG(status) + 128;	
// 		close(exec->tmp_fd);
// 		if (exec->out != STDOUT_FILENO)
// 			close(exec->out);
// 		close(get_fd(cmd->head->content, 'n', STDOUT_FILENO));
// 	}
// 	return (0);
// }


// int	execute(t_execute *exec, char **env, t_env *node, t_cmd *cmd)
// {
// 	pid_t	pid;
// 	int		counter;

// 	counter = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(exec->pipes_fd[1], STDOUT_FILENO);
// 		close(exec->pipes_fd[0]);
// 		close(exec->pipes_fd[1]);
// 		dup2(exec->tmp_fd, STDIN_FILENO);
// 		close(exec->tmp_fd);
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, SIG_DFL);
// 		while(counter < exec->pipe_num && cmd != NULL)
// 		{
// 			cmd = cmd->next;
// 			counter ++;
// 		}
// 		if(look_out_for_command(cmd) == 0)
// 			compare_cmd(cmd, node);
// 		else
// 			ft_exec(exec->commands[exec->pipe_num], env, node);
// 		exit(1);
// 	}
// 	else
// 	{
// 		close(exec->pipes_fd[1]);
// 		close(exec->tmp_fd);
// 		exec->tmp_fd = exec->pipes_fd[0];
// 	}
// 	return (0);
// }