/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:01:47 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:33:28 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	look_out_for_builtin(t_cmd *cmd)
{
	if (ft_strcmp("unset", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("cd", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("export", cmd->head->content) == 0)
		return (0);
	else if (ft_strcmp("exit", cmd->head->content) == 0)
		return (0);
	return (1);
}

void	free_exec(char ***array)
{
	int	i;
	int	j;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			j = 0;
			while (array[i][j] != NULL)
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

void	free_env_strings(char **env)
{
	int	i;

	i = 0;
	if (env != NULL)
	{
		while (env[i] != NULL)
		{
			free(env[i]);
			i ++;
		}
		free(env);
	}
}
