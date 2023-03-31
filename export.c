/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:56:44 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/31 14:23:44 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if ((str[i] < 'a' && str[i] > 'z') && (str[i] < 'A' && str[i] > 'Z')
		&& str[i] != '_')
		return (1);
	i = 1;
	while (str[i] != '\0')
	{
		if ((str[i] < 'a' && str[i] > 'z') || (str[i] < 'a' && str[i] > 'z')
			|| (str[i] < '0' && str[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_export(char *str)
{
	int i;

	i = 0;
	while(str[i] != '=')
	{
		if ((str[0] < 'A' && str[0] > 'Z') || (str[0] < 'a' && str[0] > 'z') 
			|| str[0] != '_')
		{
			return (1);
		}
		if ((str[i] < 'A' && str[i] > 'Z') || (str[i] < 'a' && str[i] > 'z') 
			|| str[i] != '_' || (str[i] < '0' && str[i] > '9'))
			return (1);
		i ++;
	}
	return (0);
}


int check_before_equal(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if(str[0] == '=')
			return (1);
		if(str[i] == '=' && str[i + 1] == '\0')
		{
			return(2);
		}
		i ++;
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
		if ((check_before_equal(token->content) == 1 && a[1] == NULL)
			|| is_valid_export(token->content) == 1)
		{
			print_error("export: ");
			print_error(token->content);
			print_error(" is not a valid identifier\n");
			// if (a[0] != NULL)
			// 	free(a[0]);
			// if (a[1] != NULL)
			// 	free(a[1]);
			// if (a != NULL)
			// 	free(a);
			g_status = 1;
			return (1);
		}
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
	// t_env	*new;

	string = ft_split(content, '=');
	if (string[1] == NULL)
	{
		return (free(string[0]), free(string[1]), free(string), 1);
	}
	/* new =  */new_node(string, node);
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
			return (1);
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
	return (0);
}
