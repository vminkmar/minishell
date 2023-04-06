/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:33:27 by kisikogl          #+#    #+#             */
/*   Updated: 2023/04/06 19:19:07 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	found_it(char *argv[], char *joined, char *path_arr[], char **env);
void	ft_free(char **argv);

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

char	**rm_redi(char **argv)
{
	char	**new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '<' || argv[i][0] == '>')
			i++;
		else
			k++;
		i++;
	}
	new = malloc(sizeof(char *) * (k + 1));
	new[k] = NULL;
	i = 0;
	k = 0;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '<' || argv[i][0] == '>')
			i++;
		else
			new[k++] = ft_strdup(argv[i]);
		i++;
	}
	ft_free(argv);
	return (new);
}

char	*search_env(char *name, t_env *node)
{
	while (node != NULL)
	{
		// printf("node: %s = ", node->name);
		// printf("%s\n", node->value);
		if (ft_strcmp(node->name, name) == 0)
		{
			return (node->value);
		}
		node = node->next;
	}
	return (NULL);
}

void	ft_exec(char *argv[], char **env, t_env *node)
{
	char	**path_arr;
	char	*path;
	char	*temp;
	char	*joined;
	int		i;

	argv = rm_redi(argv);
	if (access(argv[0], X_OK) == 0)
	{
		found_it(argv, argv[0], NULL, env);
		return ;
	}
	path = search_env("PATH", node);
	if (path == NULL)
		print_error("There is no such directory or file!\n");
	path_arr = ft_split(path, ':');
	i = 0;
	if (**argv != '/' && **argv != '.')
		temp = ft_strjoin("/", argv[0]);
	else
		temp = ft_strdup("NoCommand");
	while (path_arr[i] != NULL)
	{
		joined = ft_strjoin(path_arr[i], temp);
		if (access(joined, X_OK) == 0)
		{
			free(temp);
			found_it(argv, joined, path_arr, env);
			return ;
		}
		free(joined);
		i++;
	}
	free(temp);
	ft_free(path_arr);
	print_error("There is no such executable!\n");
	exit (127);
}

void	found_it(char *argv[], char *joined, char *path_arr[], char **env)
{
	char	free_join;

	if (argv[0] != joined)
		free_join = 'y';
	else
		free_join = 'n';
	argv[0] = joined;
	ft_free(path_arr);
	if (execve(argv[0], argv, env))
	{
		perror("Error: ");
	}
	ft_free(env);
	ft_free(argv);
	if (free_join == 'y')
		free(joined);
}
