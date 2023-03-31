/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:07:21 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/28 18:15:39 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipes(t_cmd *cmd)
{
	t_cmd 	*tmp;
	int		counter;

	counter = 0;
	tmp = cmd;
	while(tmp->next != NULL)
	{
		counter ++;
		tmp = tmp->next;
	}
	return (counter);
}

int get_token_count(t_cmd *cmd, int end)
{
	t_cmd 	*tmp;
	t_token	*token;
	int		counter;
	int		start;

	start = 0;
	counter = 0;
	tmp = cmd;
	while(start < end)
	{
		start ++;
		tmp = tmp->next;
	}
	token = tmp->head;
	while(token != NULL)
	{
		counter ++;
		token = token->next;
	}
	return (counter);
}

char	***linked_to_char(t_cmd *cmd, t_execute exec)
{
	t_token		*token;
	t_cmd		*tmp;
	int			i;
	int			j;
	int			tokens;

	tmp = cmd;
	i = 0;
	if (exec.pipes == 0)
		exec.commands = malloc(sizeof(char**) * 2);
	else
		exec.commands = malloc(sizeof(char**) * (exec.pipes + 2));
	while (tmp != NULL)
	{
		token = tmp->head;
		tokens = get_token_count(cmd, i);
		exec.commands[i] = malloc(sizeof(char *) * (tokens + 1));
		j = 0;
		while (token != NULL)
		{
			exec.commands[i][j] = ft_strdup(token->content);
			j++;
			token = token->next;
		}
		exec.commands[i][j] = NULL;
		i ++;
		tmp = tmp->next;
	}
	exec.commands[i] = NULL;
	return (exec.commands);
}
