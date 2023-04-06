/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:56:12 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 18:26:56 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fbindere_close(int a, int b, int c, int d)
{
	if (a > 2)
		close(a);
	if (b > 2)
		close(b);
	if (c > 2)
		close(c);
	if (d > 2)
		close(d);
}

void	signal_handler_and_closer(t_execute *exec)
{
	close(exec->pipes_fd[0]);
	close(exec->pipes_fd[1]);
	close(exec->tmp_fd);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	wait_all(t_execute *exec)
{
	int	counter;
	int	status;

	counter = 0;
	while (counter < exec->pipe_num + 1)
	{
		waitpid(exec->pids[counter], &status, 0);
		counter ++;
	}
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	free(exec->pids);
}
