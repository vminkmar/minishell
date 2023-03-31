/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_whitespaces_words.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:26:35 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/28 18:05:18 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_whitespace(char *input, t_cmd *cmd, t_con *con)
{
	char	*j;

	j = NULL;
	if ((con->status == NORMAL && is_whitespace(input[con->i]) == 0
			&& is_sign(input[con->i - 1]) == 1)
		&& (is_whitespace(input[con->i - 1]) == 1
			|| is_quoted(input[con->i - 1]) == 0))
	{	
		j = ft_substr(input, con->k, con->i - con->k);
		add_token(cmd, j);
		j = NULL;
		con->i++;
		con->k = con->i;
		return (0);
	}
	return (1);
}

int	skip_whitespaces(char *input, t_con *con)
{
	if (is_whitespace(input[con->i]) == 0 && con->status == NORMAL)
	{
		if (is_whitespace(input[con->i]) == 1)
			return (1);
		con->i ++;
		con->k = con->i;
	}
	return (0);
}

void	token_to_words(char *input, t_cmd *cmd, t_con *con, char *j)
{
	while (input[con->i] && con->status == NORMAL
		&& is_whitespace(input[con->i]) == 1)
	{
		if (is_quoted(input[con->i]) == 0)
			break ;
		if (is_sign(input[con->i]) == 0)
		{
			j = ft_substr(input, con->k, con->i - con->k);
			add_token(cmd, j);
			j = NULL;
			con->k = con->i;
			break ;
		}
		if (input[con->i + 1] == '\0')
		{
			j = ft_substr(input, con->k, con->i + 1 - con->k);
			add_token(cmd, j);
			j = NULL;
			con->k = con->i;
			con->i++;
			break ;
		}
		else
			con->i++;
	}
}

int	check_for_words(char *input, t_cmd *cmd, t_con *con)
{
	char	*j;

	j = NULL;
	if (is_whitespace(input[con->i]) == 1 && con->status == NORMAL)
	{
		token_to_words(input, cmd, con, j);
		return (0);
	}
	return (1);
}
