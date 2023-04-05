/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:35:10 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 22:10:08 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_first_cmd(t_cmd **cmd)
{	
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	(*cmd)->next = NULL;
	(*cmd)->head = NULL;
}

void	create_cmd(t_cmd **cmd)
{	
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	(new_cmd)->next = NULL;
	(new_cmd)->head = NULL;
	lstadd_back_cmd(cmd, new_cmd);
}

t_token	*create_token(char *j)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		print_error("Allocating Memory failed");
		exit(1);
	}
	new_token->next = NULL;
	new_token->content = j;
	new_token->state = NORMAL;
	return (new_token);
}

void	add_token(t_cmd *cmd, char *j)
{
	t_token	*new_token;

	new_token = create_token(j);
	if (cmd->head == NULL)
	{
		cmd->head = new_token;
	}
	else
		lstadd_back_token(&(cmd->head), new_token);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;

	i = 0;
	a = malloc(len * sizeof(char) + 1);
	if (a == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		*a = s[start];
		start ++;
		a++;
		i++;
	}
	*a = '\0';
	return (a - i);
}
