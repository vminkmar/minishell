/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:10:36 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:19:02 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_exit_utils(t_cmd *cmd, t_env *node, char **env, t_execute exec)
{
	t_token *token;

	token = cmd->head;
	if (check_for_numbers(token->next->content) == 0)
	{
		g_status = ft_atoi(token->next->content);
		g_status = g_status % 256;
		if (token->next->next != NULL)
			print_error("bash: exit: too many arguments\n");
		free_all_stuff(cmd, exec, env, node);
		exit (g_status);
	}
	else
	{
		g_status = 255;
		print_error("bash: exit: numeric Argument required\n");
		free_all_stuff(cmd, exec, env, node);
		exit(g_status);
	}
}

int	execute_exit(t_cmd *cmd, t_env *node, char **env, t_execute exec)
{
	t_token	*token;

	token = cmd->head;
	if (token->next == NULL)
	{
		free_all_stuff(cmd, exec, env, node);
		exit(g_status);
	}
	if (token->next->next != NULL)
	{
		print_error("bash: exit: too many arguments\n");
		g_status = 1;
		return (1);
	}
	else
		execute_exit_utils(cmd, node, env, exec);
	return (0);
}

int	execute_cd(t_cmd *cmd)
{
	const char	*str;

	str = NULL;
	if (cmd->head->next == NULL)
	{
		str = getenv("HOME");
		chdir(str);
		return (EXIT_SUCCESS);
	}
	else if (chdir(cmd->head->next->content) == -1)
	{
		print_error("No such file or directory");
		print_error("\n");
		return (EXIT_FAILURE);
	}	
	return (EXIT_FAILURE);
}

void	free_token_unset(t_env *tmp, t_token *token)
{
	t_env	*new;

	while (tmp)
	{
		if (tmp->next != NULL
			&& ft_strcmp(tmp->next->name, token->content) == 0)
		{
			new = tmp->next->next;
			free(tmp->next->name);
			free(tmp->next->value);
			free(tmp->next);
			tmp->next = new;
		}
		tmp = tmp->next;
	}
}

int	execute_unset(t_cmd *cmd, t_env **node)
{
	t_env	*tmp;
	t_token	*token;

	token = cmd->head;
	token = token->next;
	while (token && token->argument == ARGUMENT)
	{	
		if (is_valid_export(token->content) == 1
			|| ft_strcmp(token->content, "\0") == 0)
		{
			print_error("unset: ");
			print_error(token->content);
			print_error(" is not a valid identifier\n");
			g_status = 1;
			return (1);
		}
		tmp = *node;
		free_token_unset(tmp, token);
		token = token->next;
	}
	return (0);
}
