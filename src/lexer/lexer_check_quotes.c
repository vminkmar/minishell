/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:43 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/21 16:06:54 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_dq_utils(char *input, t_cmd *cmd, t_con **con)
{
	char	*j;

	j = NULL;
	if (input[(*con)->i + 1] == '\0')
	{
		j = ft_substr(input, (*con)->k, (*con)->i + 1 - (*con)->k);
		add_token(cmd, j);
		j = NULL;
		(*con)->k = (*con)->i;
		(*con)->i++;
		return (1);
	}
	return (0);
}

int	check_for_dq(char *input, t_cmd *cmd, t_con *con)
{
	if (input[con->i] == '\"' && con->status == NORMAL)
	{
		con->status = DQ;
		if (input[con->i + 1] == '\0')
		{
			if (check_for_dq_utils(input, cmd, &con) == 1)
				return (0);
		}
		else
			con->i++;
		while (input[con->i] && con->status == DQ)
		{
			if (check_for_dq_utils(input, cmd, &con) == 1)
				break ;
			if (input[con->i] == '\"' && con->status == DQ)
			{
				con->status = NORMAL;
				con->i++;
				break ;
			}
			con->i ++;
		}
		return (0);
	}
	return (1);
}

int	check_for_sq_utils(char *input, t_cmd *cmd, t_con **con)
{
	char	*j;

	j = NULL;
	if (input[(*con)->i + 1] == '\0')
	{
		j = ft_substr(input, (*con)->k, (*con)->i + 1 - (*con)->k);
		add_token(cmd, j);
		j = NULL;
		(*con)->k = (*con)->i;
		(*con)->i++;
		return (1);
	}
	return (0);
}

int	check_for_sq(char *input, t_cmd *cmd, t_con *con)
{
	if (input[con->i] == '\'' && con->status == NORMAL)
	{
		con->status = SQ;
		if (input[con->i + 1] == '\0')
		{
			if (check_for_sq_utils(input, cmd, &con) == 1)
				return (0);
		}
		else
			con->i++;
		while (input[con->i] && con->status == SQ)
		{
			if (check_for_sq_utils(input, cmd, &con) == 1)
				break ;
			if (input[con->i] == '\'' && con->status == SQ)
			{
				con->status = NORMAL;
				con->i++;
				break ;
			}
			con->i ++;
		}
		return (0);
	}
	return (1);
}
