/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:34:00 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/31 20:08:31 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_size(t_env *node)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = node;
	while(tmp != NULL)
	{
		i ++;
		tmp = tmp->next;
	}
	return (i);
}

char ** linked_env_to_strings(t_env *node)
{
	t_env	*tmp;
	int		i;
	char	**str;
	char	*new;
	int		size;

	size = get_size(node);
	i = 0;
	tmp = node;
	str = malloc(sizeof(char *) * (size + 1));
	while(tmp != NULL)
	{
		str[i] = ft_strdup(tmp->name);
		new = sl_strjoin(str[i], "=");
		free(str[i]);
		str[i] = ft_strdup(new);
		free(new);
		new = sl_strjoin(str[i], ft_strdup(tmp->value));
		free(str[i]);
		str[i] = ft_strdup(new);
		free(new);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

int look_out_for_command(t_cmd *cmd)
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


void free_env_strings(char **env)
{
	int i;

	i = 0;
	if (env != NULL)
	{
		while(env[i] != NULL)
		{
			free(env[i]);
			i ++;
		}
		free (env);
	}
}

void	checking_redirections(t_cmd *cmd, t_execute *exec)
{
	t_token *token;
	int		out;
	int		in;

	exec->in = STDIN_FILENO;
	exec->out = STDOUT_FILENO;
	while(cmd != NULL)
	{
		token = cmd->head;
		while (token != NULL)
		{
			if (token->argument == REDI)
			{
				if (ft_strcmp(token->content, "<<") == 0 && *(token->next->content) == '-')
				{
					token = token->next;
					exec->in = redirect(here_doc(token->next->content, 1), STDIN_FILENO, 'n');
				}
				else if (ft_strcmp(token->content, "<<") == 0)
					exec->in = redirect(here_doc(token->next->content, 0), STDIN_FILENO, 'n');
				else if (ft_strcmp(token->content, "<") == 0)
				{
					in = redirect(token->next->content, STDIN_FILENO, 'n');
					if (exec->in == STDIN_FILENO)
						exec->in = in;
					else
						close(in);
				}
				else
				{
					if (ft_strcmp(token->content, ">") == 0)
						out = redirect(token->next->content, STDOUT_FILENO, 'n');
					else if (ft_strcmp(token->content, ">>") == 0)
						out = redirect(token->next->content, STDOUT_FILENO, 'a');
					if (exec->out == STDOUT_FILENO)
						exec->out = out;
					else
						close(out);
				}
				token = token->next;
			}
			token = token->next;
		}
		cmd = cmd->next;
	}

}


int	connector(char *input, t_cmd *cmd, t_env *node)
{
	t_execute	exec;
	char		**env;

	if (lexer(input, cmd) == 1)
		return (1);
	cmd = parse_stuff(cmd);
	if (cmd == NULL)
		return (1);
	if (expander(cmd, node) == 1)
		return (1);
	checking_redirections(cmd, &exec);	//new function
	exec.pipes = count_pipes(cmd);
	exec.commands = linked_to_char(cmd, exec);
	env =  linked_env_to_strings(node);
	if (exec.pipes == 0)
	{
		if (look_out_for_command(cmd) == 0)
		{
			if(compare_cmd(cmd, node) == 1)
				return(1);
		}
		else
		{
			exec.pipe_num = 0;
			execute_without_pipes(&exec, env, node, cmd);
		}
	}
	else
	{
		dup2(exec.out, STDOUT_FILENO);
		dup2(exec.in, STDIN_FILENO);
		ft_pipe(cmd, node, exec, env);
	}
	dup2(exec.out, STDOUT_FILENO);
	dup2(exec.in, STDIN_FILENO);
	free_exec(exec.commands);
	free_env_strings(env);
	return (0);
}
