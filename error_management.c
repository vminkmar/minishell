/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:36:27 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 22:08:15 by vminkmar         ###   ########.fr       */
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

void	put_error(char c)
{
	write(2, &c, 1);
}

void	print_error(char *str)
{
	int	end;

	end = 0;
	while (str[end] != '\0')
	{
		put_error(str[end]);
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
