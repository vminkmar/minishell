/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:10:36 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 17:38:42 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->head;
	if (token->next == NULL)
		exit(g_status);
	if (token->next->next != NULL)
	{
		print_error("bash: exit: too many arguments\n");
		g_status = 1;
		return (1);
	}
	else
	{
		if (check_for_numbers(token->next->content) == 0)
		{
			g_status = ft_atoi(token->next->content);
			g_status = g_status % 256;
			if (token->next->next != NULL)
				print_error("bash: exit: too many arguments\n");
			exit (g_status);
		}
		else
		{
			g_status = 255;
			print_error("bash: exit: numeric Argument required\n");
			exit(g_status);
		}
	}
}

void	execute_echo(t_cmd *cmd)
{
	t_token	*token;
	int		flag;

	flag = 0;
	token = cmd->head;
	if (token->next == NULL)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (token->next != NULL && (token->next->argument == ARGUMENT
			|| token->next->argument == OPTION))
	{
		token = token->next;
		while (token != NULL && token->argument == OPTION
			&& check_option(token->content) == 0)
		{
			flag = 1;
			if (token->next == NULL)
				ft_putstr_fd("", STDOUT_FILENO);
			token = token->next;
		}
		while (token && (token->argument == ARGUMENT
				|| token->argument == OPTION))
		{
			if (token->next == NULL || (token->next->argument != ARGUMENT
					&& token->next->argument != OPTION))
			{
				ft_putstr_fd(token->content, STDOUT_FILENO);
				if (flag != 1)
					ft_putstr_fd("\n", STDOUT_FILENO);
			}
			else
			{
				ft_putstr_fd(token->content, STDOUT_FILENO);
				if (token->next != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
			}
			token = token->next;
		}
	}
	g_status = 0;
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

int	execute_unset(t_cmd *cmd, t_env **node)
{
	t_env	*tmp;
	t_env	*new;
	t_token	*token;

	token = cmd->head;
	token = token->next;
	while (token && token->argument == ARGUMENT)
	{	
		if (is_valid_export(token->content) == 1 || ft_strcmp(token->content, "\0") == 0)
		{
			print_error("unset: ");
			print_error(token->content);
			print_error(" is not a valid identifier\n");
			g_status = 1;
			return (1);
		}
		tmp = *node;
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
		token = token->next;
	}
	return (0);
}
