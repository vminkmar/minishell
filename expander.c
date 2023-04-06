/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:37:04 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 15:50:16 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token(char *new_token, char *tmp)
{
	free(new_token);
	return (tmp);
}

char	*expand_rest(char *content, int *i, int *j)
{
	char	*new_content;
	char	*new_token;

	new_content = NULL;
	new_token = ft_strdup("");
	*j = *i;
	while (content[*i] != '\'' && content[*i] != '\"' && content[*i] != '\0'
		&& content[*i] != '$')
		(*i)++;
	new_content = ft_substr(content, *j, *i - *j);
	new_token = sl_strjoin_free(new_token, new_content, 3);
	content = ft_strdup(new_token);
	free(new_token);
	return (content);
}

char	*expand_variables(char *content, t_env *env)
{
	int		i;
	int		j;
	char	*new_token;

	i = 0;
	j = 0;
	new_token = ft_strdup("");
	while (content[i] != '\0')
	{
		if (content[i] == '\"')
			j = i;
		if (content[i] == '\"')
			new_token = sl_strjoin_free(new_token
				, expand_variables_quoted(content, env, &i, &j), 3);
		if (content[i] == '\'')
			new_token = sl_strjoin_free(new_token, expand_sq(content, &i, &j), 3);
		if (content[i] == '$')
			new_token = sl_strjoin_free(new_token, expand_variables_unquoted(content, env, &i, &j), 3);
		if (content[i] != '\'' && content[i] != '\"' && content[i] != '\0')
			new_token = sl_strjoin_free(new_token, expand_rest(content, &i, &j), 3);
	}
	return (new_token);
}

int	expander(t_cmd *cmd, t_env *env)
{
	t_token	*token;
	char	*tmp;

	while (cmd != NULL)
	{
		token = cmd->head;
		while (token != NULL)
		{
			tmp = token->content;
			token->content = expand_variables(token->content, env);
			free(tmp);
			token = token->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
