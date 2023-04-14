/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:06:56 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/01 17:34:17 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_stuff(t_cmd *cmd)
{
	t_token	*tmp;
	t_cmd	*search;

	tmp = NULL;
	if (check_command(cmd) == 1)
		return (NULL);
	search = cmd;
	while (search != NULL)
	{
		tmp = search->head;
		if (check_token_and_variables(tmp) == 1)
			return (NULL);
		search = search->next;
	}
	return (cmd);
}
