/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:09:30 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/21 16:17:43 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_options(t_token *token)
{
	if (token->content[0] == '-' && token->content[1] == 'n')
	{
		if (compare_char(token->content, 'n') == 0
			&& look_quotes(token->content) == 0)
			token->argument = OPTION;
		else
			token->argument = ARGUMENT;
		return (0);
	}
	return (1);
}

int	check_for_variables(t_token *token)
{
	if (ft_strcmp(">", token->content) == 0
		|| ft_strcmp(">>", token->content) == 0
		|| ft_strcmp("<", token->content) == 0
		|| ft_strcmp("<<", token->content) == 0)
		token->argument = REDI;
	if (token->argument == REDI)
	{
		if (token->next != NULL)
		{
			token = token->next;
			token->argument = FILENAME;
		}
		if (token == NULL)
		{
			print_error("syntax error near unexpected token\n");
			return (-1);
		}
		return (1);
	}
	else if (check_for_options(token) == 0)
		return (0);
	else
		token->argument = ARGUMENT;
	return (0);
}

void	check_command(t_cmd *cmd)
{
	if (ft_strcmp(">", cmd->head->content) == 0
		|| ft_strcmp(">>", cmd->head->content) == 0
		|| ft_strcmp("<", cmd->head->content) == 0
		|| ft_strcmp("<<", cmd->head->content) == 0)
		cmd->head->argument = REDI;
	else
	{
		cmd->head->content = make_it_small(cmd->head->content);
		cmd->head->argument = COMMAND;
	}
}

int	check_token(t_token *token)
{
	if (check_quotes(token) == 1)
		return (1);
	if (token->argument == COMMAND)
		return (0);
	check_rd_in(token);
	check_rd_out(token);
	return (0);
}

int	check_token_and_variables(t_token *tmp, t_cmd *search)
{
	tmp = search->head;
	while (tmp != NULL)
	{
		if (check_token(tmp) == 1)
		{
			print_error("check for unclosed quotes\n");
			return (1);
		}
		if (check_for_variables(tmp) == 1)
		{
			tmp = tmp->next;
			if (check_token(tmp) == 1)
			{
				print_error("check for unclosed quotes\n");
				return (1);
			}
		}
		if (check_for_variables(tmp) == -1)
			return (1);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (0);
}
