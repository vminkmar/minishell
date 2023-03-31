/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:36:27 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/30 19:52:48 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_token(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_token	*del;

	if (cmd != NULL)
	{	
		while ((*cmd)->next != NULL)
		{
			tmp = (*cmd);
			while ((*cmd)->head->next != NULL)
			{
				del = (*cmd)->head;
				(*cmd)->head->next = (*cmd)->head->next->next;
				free(del->content);
				free(del);
				
			}
			(*cmd) = (*cmd)->next;
			free(tmp);
		}
	}
	cmd = NULL;
}

void free_list(t_cmd **cmd)
{
	t_token	*tmp;
	t_token	*del;
	t_cmd	*temp;

	if(cmd != NULL)
	{	
		while ((*cmd)->next != NULL)
		{
			tmp = (*cmd)->head;
			while (tmp->next != NULL)
			{
				del = tmp;
				tmp = tmp->next;
				free(del->content);
				free(del);
			}
			temp = (*cmd);
			(*cmd) = (*cmd)->next;
			free(temp);
		}
	}
	cmd = NULL;
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
		while ((*node)->next != NULL)
		{
			temp = (*node);
			while ((*node)->next != NULL)
			{
				temp = (*node);
				(*node) = (*node)->next;
				free(temp->value);
				free(temp->name);
				free(temp);
			}
		}
	}

}

void free_exec(char ***array)
{
	int	i;
	int	j;

	i = 0;
	if (array != NULL)
	{
		while(array[i] != NULL)
		{
			j = 0;
			while(array[i][j] != NULL)
			{
				free(array[i][j]);
				j ++;
			}
			free(array[i]);
			i ++;
		}
		free(array);
	}
}
