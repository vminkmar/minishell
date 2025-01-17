/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:56:44 by vminkmar          #+#    #+#             */
/*   Updated: 2024/03/06 20:05:45 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_node_exec(t_token *token, char **a)
{
	if ((check_before_equal(token->content) == 1 || a[1] == NULL)
		|| is_valid_export(a[0]) == 1)
	{
		print_error("export: ");
		print_error(token->content);
		print_error(" is not a valid identifier\n");
		g_status = 1;
		return (1);
	}
	return (0);
}

int	get_new_node_exec(t_token *token, t_env **node)
{
	char	**a;

	if (search_sign(token->content, '=') == 0)
	{
		a = split_env(token->content, '=');
		if (check_before_equal(token->content) == 2 && a[1] == NULL)
			a[1] = ft_strdup("");
		if (check_new_node_exec(token, a) == 1)
			return (1);
		if (check_string(a[0]) == 1)
			return (1);
		add_node(a, node);
		free(a[0]);
		free(a[1]);
		free(a);
	}
	else
	{
		add_node(&token->content, node);
	}
	return (0);
}

int	create_new_env(t_env **node, char *content)
{
	char	**string;
	t_env	*new;

	string = ft_split(content, '=');
	if (string[1] == NULL)
	{
        return (free(string[0]), free(string[1]), free(string), 1);
    }	
	new = new_node(string, node);
    if (new == NULL)
	{
        return (free(string[0]), free(string[1]), free(string), 1);
    }	
	free(string[0]);
	free(string[1]);
	free(string);
	return (0);
}

void	print_export(t_env *node)
{
	while (node)
	{
		if (node->value == NULL && search_sign(node->name, '=') == 1)
			printf("declare -x %s\n", node->name);
		else if (node->value == NULL)
			printf("declare -x %s=\"\"\n", node->name);
		else
			printf("declare -x %s=%s\n", node->name, node->value);
		node = node->next;
	}
}

int	execute_export(t_cmd *cmd, t_env **node)
{
	t_token	*token;

	token = cmd->head;
	if (node == NULL || *node == NULL)
	{
		if (create_new_env(node, cmd->head->next->content) == 1)
			return (EXIT_FAILURE);
	}
	if (token->next == NULL || token->next->argument != ARGUMENT)
		print_export(*node);
	else
	{
		token = token->next;
		while (token)
		{
			if (token->argument != ARGUMENT)
				break ;
			get_new_node_exec(token, node);
			token = token->next;
		}
	}
	return (EXIT_SUCCESS);
}
