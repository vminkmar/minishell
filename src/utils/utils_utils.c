/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:18:54 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/22 14:20:29 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstadd_back_token(t_token **lst, t_token *new)
{	
	t_token	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{	
	t_cmd	*tmp;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{	
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_quoted(char c)
{
	if (c == '\'' || c == '\"')
		return (0);
	return (1);
}

int	is_sign(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\0')
		return (0);
	return (1);
}

int	is_whitespace(char c)
{
	if (c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == ' ')
		return (0);
	return (1);
}
