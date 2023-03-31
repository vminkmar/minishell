/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipes_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:27:39 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/21 15:35:47 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*check_for_pipes(t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		while (cmd->next != NULL)
			cmd = cmd->next;
	}
	return (cmd);
}

int	check_for_redirecions(char *input, t_cmd *cmd, t_con *con)
{
	char	*j;

	j = NULL;
	if (input[con->i] == '>' && con->status == NORMAL)
	{
		if (input[con->i + 1] == '>')
		{
			con->i ++;
		}
		j = ft_substr(input, con->k, con->i + 1 - con->k);
		add_token(cmd, j);
		j = NULL;
		con->i++;
		con->k = con->i;
		if (input[con->i - 1] == '>')
		{
			cmd->head->type = D_REDIR_IN;
		}
		else
			cmd->head->type = REDIR_IN;
		return (0);
	}
	return (1);
}

int	add_if_pipe(char *input, t_cmd *cmd, t_con *con)
{
	if (input[con->i] == '|' && con->status == NORMAL)
	{	
		create_cmd(&cmd);
		con->i ++;
		con->k = con->i;
		return (0);
	}
	return (1);
}

int	check_for_token_for_redirections(char *input, t_cmd *cmd, t_con *con)
{
	char	*j;

	j = NULL;
	if (input[con->i] == '<' && con->status == NORMAL)
	{
		if (input[con->i + 1] == '<')
			con->i ++;
		j = ft_substr(input, con->k, con->i + 1 - con->k);
		add_token(cmd, j);
		j = NULL;
		con->i++;
		con->k = con->i;
		return (0);
	}
	return (1);
}
