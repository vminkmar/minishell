/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:54:05 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/21 16:07:35 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sq_utils(t_token *tmp, int *i)
{
	if (tmp->state == SQ && tmp->content[*i] == '\''
		&& tmp->content[*i + 1] == '\0')
	{
		tmp->type = QUOTES;
		tmp->state = NORMAL;
		return (0);
	}
	if (tmp->state == SQ && tmp->content[*i] == '\'')
	{
		tmp->state = NORMAL;
		tmp->type = WORD;
		return (0);
	}
	return (1);
}

int	check_sq(t_token *tmp, int *i)
{
	while (tmp->content[*i] != '\0')
	{
		if (tmp->state == NORMAL && tmp->content[*i] == '\'')
		{	
			tmp->state = SQ;
			(*i)++;
		}
		if (check_sq_utils(tmp, i) == 0)
			return (0);
		if (tmp->content[*i + 1] == '\0' && tmp->state == SQ)
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_dq_utils(t_token *tmp, int *i)
{
	if (tmp->state == DQ && tmp->content[*i] == '\"'
		&& tmp->content[*i + 1] == '\0')
	{
		if (tmp->type != QVAR)
			tmp->type = D_QUOTES;
		tmp->state = NORMAL;
		return (0);
	}
	if (tmp->state == DQ && tmp->content[*i] == '\"')
	{
		if (tmp->type != QVAR)
			tmp->type = WORD;
		tmp->state = NORMAL;
		return (0);
	}
	return (1);
}

int	check_dq(t_token *tmp, int *i)
{
	while (tmp->content[*i] != '\0')
	{
		if (tmp->state == NORMAL && tmp->content[*i] == '\"')
		{	
			tmp->state = DQ;
			(*i)++;
		}	
		if (tmp->state == DQ && tmp->content[*i] == '$')
			tmp->type = QVAR;
		if (check_dq_utils(tmp, i) == 0)
			return (0);
		if (tmp->content[*i + 1] == '\0' && tmp->state == DQ)
			return (1);
		(*i)++;
	}
	return (0);
}

int	check_quotes(t_token *token)
{
	int	i;

	i = 0;
	while (token->content[i] != '\0')
	{
		if (token->content[i] == '\'')
			if (check_sq(token, &i) == 1)
				return (1);
		if (token->content[i] == '\"')
			if (check_dq(token, &i) == 1)
				return (1);
		i ++;
	}
	return (0);
}
