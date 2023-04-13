/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:13:56 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:19:46 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	*a;

	a = getcwd(NULL, 0);
	ft_putstr_fd(a, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

void	execute_env(t_env *node)
{
	while (node != NULL)
	{
		if (node->value != NULL)
		{
			ft_putstr_fd(node->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(node->value, 1);
			ft_putstr_fd("\n", 1);
		}
		node = node->next;
	}
}

int	rest(char *str)
{
	if (ft_strcmp("echo", str) == 0 || ft_strcmp("env", str) == 0
		|| ft_strcmp("unset", str) == 0 || ft_strcmp("pwd", str) == 0
		|| ft_strcmp("export", str) == 0 || ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}

int	compare_cdm_utils(t_cmd *cmd, t_env *node, t_execute exec, char **env)
{
	if (ft_strcmp("pwd", cmd->head->content) == 0)
	{
		execute_pwd();
	}
	else if (ft_strcmp("export", cmd->head->content) == 0)
	{
		if (execute_export(cmd, &node) == 1)
			return (1);
	}
	else if (ft_strcmp("exit", cmd->head->content) == 0)
	{
		if (execute_exit(cmd, node, env, exec) == 1)
			return (1);
	}
	return (0);
}

int	compare_cmd(t_cmd *cmd, t_env *node, t_execute exec, char **env)
{
	if (ft_strcmp("echo", cmd->head->content) == 0)
	{
		execute_echo(cmd);
	}	
	if (ft_strcmp("env", cmd->head->content) == 0)
		execute_env(node);
	else if (ft_strcmp("unset", cmd->head->content) == 0)
	{
		if (execute_unset(cmd, &node) == 1)
			return (1);
	}
	else if (ft_strcmp("cd", cmd->head->content) == 0)
	{
		execute_cd(cmd);
	}
	if (compare_cdm_utils(cmd, node, exec, env) == 1)
		return (1);
	return (0);
}
