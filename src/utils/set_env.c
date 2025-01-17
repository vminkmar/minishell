/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:33:53 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 21:34:17 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstadd_back_new_node(t_env **lst, t_env *new)
{	
	t_env	*tmp;

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

t_env	*new_node(char *a[], t_env **node)
{
	t_env	*new_node;

	(void) node;
	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		print_error("Memory Allocation failed");
		return (NULL);
	}
	new_node->name = ft_strdup(a[0]);
	new_node->value = ft_strdup(a[1]);
	new_node->next = NULL;
	free(a[0]);
	free(a[1]);
	free(a);
	return (new_node);
}

int	set_env(char *env[], t_env **node)
{
	int		i;
	char	**a;
	t_env	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		a = split_env(env[i], '=');
		if (a[1] == NULL)
			free_all(node);
		tmp = new_node(a, node);
		if (tmp == NULL)
		{
			free_all(node);
			return (EXIT_FAILURE);
		}
		lstadd_back_new_node(node, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
