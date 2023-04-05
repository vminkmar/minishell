/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 06:33:27 by kisikogl          #+#    #+#             */
/*   Updated: 2023/04/05 15:58:53 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	found_it(char *argv[], char *joined, char *path_arr[], char **env);
void	ft_free(char **argv);

void	ft_free(char **argv)
{
	int	i;

	i = 0;
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
		{
			new[k] = ft_strdup(argv[i]);
			k++;
		}
		i++;
	}
	ft_free(argv);
	return (new);
}

char *search_env(char *name, t_env *node)
{
	while(node != NULL)
	{
		if(ft_strcmp(node->name, name) == 0)
		{
			return(node->value);
		}
		node = node->next;
	}
	return (NULL);
}


// Takes as argument a list of Strings. The first one is the cmd/executable,
// the other ones are options/arguments to the executable
void	ft_exec(char *argv[], char **env, t_env *node)
{
	char	**path_arr;
	char	*path;
	char	*temp;
	char	*joined;
	int		i;

	argv = rm_redi(argv);
	path = search_env("PATH", node);
	if (path == NULL)
		print_error("There is no such directory or file!\n");
	path_arr = ft_split(path, ':');
	i = 0;
	temp = ft_strjoin("/", argv[0]);
	while (path_arr[i] != NULL)
	{
		joined = ft_strjoin(path_arr[i], temp);
		if (access(joined, X_OK) == 0)
		{
			free(temp);
			found_it(argv, joined, path_arr, env);
			return ;
		}
		if (access(argv[0], X_OK) == 0)
		{
			free(temp);
			free(joined);
			found_it(argv, argv[0], path_arr, env);
			return ;
		}
		free(joined);
		i++;
	}
	free(temp);
	ft_free(path_arr);
	print_error("There is no such executable!\n");
	return ;
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
	execve(argv[0], argv, env);
	perror("Error: ");
	if (free_join == 'y')
		free(joined);
	exit (1);
}
