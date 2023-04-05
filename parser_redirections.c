/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:11:26 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/21 16:11:38 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_rd_in(t_token *tmp)
{
	int	i;

	i = 0;
	if (tmp->state == NORMAL && tmp->content[i] == '>')
		tmp->type = REDIR_IN;
	if (tmp->content[i + 1] == '>')
		tmp->type = D_REDIR_IN;
}

void	check_rd_out(t_token *tmp)
{
	int	i;

	i = 0;
	if (tmp->state == NORMAL && tmp->content[i] == '<')
		tmp->type = REDIR_IN;
	if (tmp->content[i + 1] == '<')
		tmp->type = D_REDIR_IN;
}