/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:10:56 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 23:36:07 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value_check_dollar(char **str, int *i)
{
	int		j;
	int		k;
	char	*temp;

	j = 0;
	k = 0;
	if (check_after_dollar(str[*i]) == 2)
	{
		str[*i] = remove_dollar(str[*i]);
		k = ft_strlen(str[*i]);
		temp = str[*i];
		if (str[*i][0] == '\'')
			str[*i] = expand_sq(str[*i], &j, &k);
		if (str[*i][0] == '\"')
			str[*i] = remove_dq(str[*i], &j);
		return (free(temp), 0);
	}
	if (check_after_dollar(str[*i]) == 1)
		return (0);
	if (check_question_mark(str[*i]) == 0)
	{
		str[*i] = ft_strdup(remove_dollar(change_question_mark(str[*i])));
		return (0);
	}
	return (1);
}

char	*change_value_util(char **str, t_env *env, int *i)
{
	int		flag;
	char	*dollar;
	t_env	*node;

	node = env;
	flag = 0;
	if (change_value_check_dollar(str, i) == 0)
		return (str[*i]);
	dollar = remove_dollar(str[*i]);
	while (node != NULL)
	{
		if (ft_strcmp(node->name, dollar) == 0)
		{
			flag = 1;
			str[*i] = remove_variable(node->value);
			break ;
		}
		node = node->next;
	}
	if (flag == 0)
	{
		str[*i] = ft_strdup("");
	}
	return (free(dollar), str[*i]);
}

char	*change_value(char **str, t_env *env, int i, int j)
{
	char	*new;

	new = ft_strdup("");
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$')
			{
				change_value_util(str, env, &i);
			}
			j++;
		}
		new = sl_strjoin_free(new, str[i], 1);
		i++;
	}
	ft_free(str);
	return (new);
}
