/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:10:36 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/04 12:06:21 by vminkmar         ###   ########.fr       */
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
	if (node == NULL)
	{
		exit(1); //error_management
	}
	new_node->name = ft_strdup(a[0]);
	new_node->value =  ft_strdup(a[1]);
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
			return(0);
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
	//error handling if name == NULL
}



void	execute_env(t_env *node)
{
	while (node != NULL)
	{
		// if(node->name == NULL)
		// 	error;
		if (node->value != NULL)
			ft_putstr_fd(node->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(node->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		node = node->next;
	}
}

int	check_for_numbers(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i ++;
	}
	return (1);
}

int	execute_exit(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->head;
	if (token->next == NULL)
		exit(g_status);
	if (token->next->next != NULL)
	{
		print_error("bash: exit: too many arguments");
		g_status = 1;
		return (1);
	}
	else
	{
		if (check_for_numbers(token->next->content) == 0)
		{
			g_status = ft_atoi(token->content);
			if (g_status > 255 || g_status < 0)
				g_status = 255;
			if (token->next->next != NULL)
				print_error("bash: exit: too many arguments");
			exit (g_status);
		}
		else
			exit(g_status);
	}
}

int	check_option(char *str)
{
	if (str[0] == '-' && str[1] == 'n')
		return (0);
	return (1);
}

void	execute_echo(t_cmd *cmd)
{
	t_token	*token;
	int		flag;

	flag = 0;
	token = cmd->head;
	if (token->next == NULL)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (token->next != NULL && (token->next->argument == ARGUMENT
		|| token->next->argument == OPTION))
	{
		token = token->next;
		while(token != NULL && token->argument == OPTION && check_option(token->content) == 0)
		{
				flag = 1;
				if (token->next == NULL)
					ft_putstr_fd("", STDOUT_FILENO);
				token = token->next;
		}
		while (token && (token->argument == ARGUMENT || token->argument == OPTION))
		{
			if (token->next == NULL || (token->next->argument != ARGUMENT
				&& token->next->argument != OPTION))
			{
				ft_putstr_fd(token->content, STDOUT_FILENO);
				if(flag != 1)
					ft_putstr_fd("\n", STDOUT_FILENO);		
			}
			else
			{
				ft_putstr_fd(token->content,  STDOUT_FILENO);
				if (token->next != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
			}
			token = token->next;
		}
	}
}

void	execute_pwd()
{
	char	*a;

	a = getcwd(NULL, 0);
	// if (a == NULL)
	// 	error;
	ft_putstr_fd(a, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	execute_cd(t_cmd *cmd)
{
	const char	*str;

	str = NULL;
	if (cmd->head->next == NULL)
	{
		str = getenv("HOME");
		chdir(str);
	}
	else if (chdir(cmd->head->next->content) == -1)
		print_error("No such file or directory");
		print_error("\n");
		
}

int	execute_unset(t_cmd *cmd, t_env **node)
{
	t_env	*tmp;
	t_env	*new;
	t_token	*token;

	token = cmd->head;
	token = token->next;
	while (token && token->argument == ARGUMENT)
	{	
		if (is_valid_export(token->content) == 1)
		{
			print_error("unset: ");
			print_error(token->content);
			print_error(" is not a valid identifier\n");
			g_status = 1;
			return (1);
		}
		tmp = *node;
		while (tmp)
		{
			if (tmp->next != NULL && ft_strcmp(tmp->next->name, token->content) == 0)
			{
				new = tmp->next->next;
				free(tmp->next->name);
				free(tmp->next->value);
				free(tmp->next);
				tmp->next = new;
			}
			tmp = tmp->next;
		}
		token = token->next;
	}
	return (0);
}

int rest(char *str)
{
	if(ft_strcmp("echo", str) == 0 || ft_strcmp("env", str) == 0 || ft_strcmp("unset", str) == 0 || ft_strcmp("pwd", str) == 0
		|| ft_strcmp("export", str) == 0 || ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}

int	compare_cmd(t_cmd *cmd, t_env *node)
{
	if (ft_strcmp("echo", cmd->head->content) == 0)	
	{
		execute_echo(cmd);
	}	
	if (ft_strcmp("env", cmd->head->content) == 0)
		execute_env(node);
	else if (ft_strcmp("unset", cmd->head->content) == 0)
	{
		if (execute_unset(cmd, &node) == 1)
			return (1);
	}
	else if (ft_strcmp("cd", cmd->head->content) == 0)
		execute_cd(cmd);
	else if (ft_strcmp("pwd", cmd->head->content) == 0)
		execute_pwd();
	else if (ft_strcmp("export", cmd->head->content) == 0)
	{	
		if (execute_export(cmd, &node) == 1)
			return (1);
	}
	else if (ft_strcmp("exit", cmd->head->content) == 0)
	{
		if (execute_exit(cmd) == 1)
			return (1);
	}
	return (0);
}