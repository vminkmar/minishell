/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:06:56 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/21 16:11:22 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_stuff(t_cmd *cmd)
{
	t_token	*tmp;
	t_cmd	*search;

	tmp = NULL;
	check_command(cmd);
	search = cmd;
	while (search != NULL)
	{
		if (check_token_and_variables(tmp, search) == 1)
			return (NULL);
		search = search->next;
	}
	return (cmd);
}
