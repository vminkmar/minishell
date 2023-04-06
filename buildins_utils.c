/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:12:44 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 17:31:54 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(char *a[], t_env **node)
{
	t_env	*new_node;
	t_env	*tmp;

	tmp = *node;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, a[0]) == 0)
		{
			tmp->value = ft_strdup(a[1]);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		exit(1);
	}
	new_node->name = ft_strdup(a[0]);
	new_node->value = ft_strdup(a[1]);
	new_node->next = NULL;
	lstadd_back_new_node(node, new_node);
}

int	search_sign(char *str, int sign)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sign)
			return (0);
		i ++;
	}
	return (1);
}

void	get_new_node(t_token *token, t_env **node)
{
	char	**a;

	a = NULL;
	if (search_sign(token->content, '=') == 0)
	{
		a = ft_split(token->content, '=');
		add_node(a, node);
		free(a[0]);
		free(a[1]);
		free(a);
	}
	else
	{
		add_node(&token->content, node);
	}
}

int	check_option(char *str)
{
	if (str[0] == '-' && str[1] == 'n')
		return (0);
	return (1);
}

int	check_for_numbers(char *str)
{
	int	i;

	i = 0; 
	if(str[0] == '+' || str[0] == '-')
		i++;
	if(str[i] == '+' || str[i] == '-')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i ++;
	}
	return (1);
}
