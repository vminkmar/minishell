/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:07:21 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 20:23:08 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		counter;

	counter = 0;
	tmp = cmd;
	while (tmp->next != NULL)
	{
		counter ++;
		tmp = tmp->next;
	}
	return (counter);
}

int	get_token_count(t_cmd *cmd)
{
	t_token	*token;
	int		counter;

	counter = 0;
	token = cmd->head;
	while (token != NULL)
	{
		counter ++;
		token = token->next;
	}
	return (counter);
}

char	***linked_to_char(t_cmd *cmd, t_execute exec)
{
	t_token		*token;
	int			i;
	int			j;
	int			tokens;

	i = 0;
	exec.commands = malloc(sizeof(char **) * (exec.pipes + 2));
	while (cmd != NULL)
	{
		token = cmd->head;
		tokens = get_token_count(cmd);
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
		cmd = cmd->next;
	}
	exec.commands[i] = NULL;
	return (exec.commands);
}

int	get_size(t_env *node)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = node;
	while (tmp != NULL)
	{
		i ++;
		tmp = tmp->next;
	}
	return (i);
}

char	**linked_env_to_strings(t_env *node)
{
	int		i;
	char	**str;
	char	*new;
	int		size;

	size = get_size(node);
	i = 0;
	str = malloc(sizeof(char *) * (size + 1));
	while (node != NULL)
	{
		str[i] = ft_strdup(node->name);
		new = sl_strjoin(str[i], "=");
		new = sl_strjoin(str[i], ft_strdup(node->value));
		str[i] = ft_strdup(new);
		free(new);
		i++;
		node = node->next;
	}
	str[i] = NULL;
	return (str);
}
