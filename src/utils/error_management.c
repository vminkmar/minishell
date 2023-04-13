/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:36:27 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:32:35 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_cmd *cmd)
{
	t_token	*tmp;
	t_token	*del;
	t_cmd	*temp;

	while (cmd != NULL)
	{
		tmp = cmd->head;
		while (tmp != NULL)
		{
			del = tmp;
			tmp = tmp->next;
			free(del->content);
			free(del);
		}
		temp = cmd;
		cmd = cmd->next;
		free(temp);
	}
}

void	print_error(char *str)
{
	int	end;

	end = 0;
	while (str[end] != '\0')
	{
		write(2, &str[end], 1);
		end ++;
	}
}

void	free_all(t_env **node)
{
	t_env	*temp;

	if (node != NULL)
	{
		temp = (*node);
		while ((*node) != NULL)
		{
			temp = (*node);
			(*node) = (*node)->next;
			free(temp->value);
			free(temp->name);
			free(temp);
		}
	}
}

void	ft_free(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_all_stuff(t_cmd *cmd, t_execute exec, char **env, t_env *node)
{
	free_exec(exec.commands);
	free_env_strings(env);
	free_all(&node);
	free_list(cmd);
}
