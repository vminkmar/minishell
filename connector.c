/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:34:00 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 13:20:36 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_out_for_command(t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("env", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("unset", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("cd", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("pwd", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("export", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("exit", cmd->head->content) == 0)
		return (0);
	return (1);
}

void	checking_redirections(t_cmd *cmd, t_execute *exec, int end, t_env *env)
{
	t_token	*token;
	int		out;
	int		in;
	int		counter;

	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
	counter = 0;
	while (counter < end)
	{
		cmd = cmd->next;
		counter++;
	}
	token = cmd->head;
	while (token != NULL)
	{
		if (token->argument == REDI)
		{
			if (ft_strcmp(token->content, "<<") == 0 && *(token->next->content) == '-')
			{
				token = token->next;
				exec->in = redirect(here_doc(token->next->content, 1, env), STDIN_FILENO, 'n');
			}
			else if (ft_strcmp(token->content, "<<") == 0)
				exec->in = redirect(here_doc(token->next->content, 0, env), STDIN_FILENO, 'n');
			else if (ft_strcmp(token->content, "<") == 0)
			{
				if(exec->in != STDIN_FILENO)
					close(in);
				in = redirect(token->next->content, STDIN_FILENO, 'n');
				exec->in = in;
			}
			else
			{
				if (exec->out != STDOUT_FILENO)
					close(out);
				if (ft_strcmp(token->content, ">") == 0)
					out = redirect(token->next->content, STDOUT_FILENO, 'n');
				else if (ft_strcmp(token->content, ">>") == 0)
					out = redirect(token->next->content, STDOUT_FILENO, 'a');
				exec->out = out;
			}
			token = token->next;
		}
		token = token->next;
	}
}

int look_out_for_builtin(t_cmd *cmd)
{
	if (ft_strcmp("unset", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("cd", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("export", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("exit", cmd->head->content) == 0)
		return (0);
	return (1);
}

int	connector(char *input, t_cmd *cmd, t_env *node)
{
	t_execute	exec;
	char		**env;

	exec.pipe_num = 0;
	if (lexer(input, cmd) == 1)
		return (1);
	cmd = parse_stuff(cmd);
	if (cmd == NULL)
		return (1);
	if (expander(cmd, node) == 1)
		return (1);
	exec.pipes = count_pipes(cmd);
	exec.commands = linked_to_char(cmd, exec);
	env = linked_env_to_strings(node);
	if (exec.pipes == 0)
	{
		if (look_out_for_builtin(cmd) == 0)
		{
			if (compare_cmd(cmd, node) == 1)
				return (1);
		}
		else
			ft_pipe(cmd, node, &exec, env);
	}
	else
 		ft_pipe(cmd, node, &exec, env);
	free_exec(exec.commands);
	free_env_strings(env);
	return (0);
}
