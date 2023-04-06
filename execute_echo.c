/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:56:42 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:45:21 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	true_execute_echo(t_token *token, int flag)
{
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
		true_execute_echo(token, flag);
	}
	g_status = 0;
}
