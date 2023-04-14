/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:21:11 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/13 16:43:56 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	lexer_two(char *input, t_cmd *tmp, t_con *con)
{
	if (check_for_redirecions(input, tmp, con) == 0)
		return (0);
	else if (add_if_pipe(input, tmp, con) == 0)
		return (0);
	else if (check_for_token_for_redirections(input, tmp, con) == 0)
		return (0);
	else if (check_for_words(input, tmp, con) == 0)
		return (0);
	return (1);
}

int	lexer(char *input, t_cmd *cmd)
{
	t_con	con;
	t_cmd	*tmp;

	con.i = 0;
	con.k = 0;
	con.status = NORMAL;
	input = ft_strtrim(input, " ");
	while (input[con.i])
	{
		tmp = check_for_pipes(cmd);
		if (lexer_whitespace(input, tmp, &con) == 0)
			continue ;
		else if (skip_whitespaces(input, &con) == 1)
			break ;
		else if (check_for_dq(input, tmp, &con) == 0)
			continue ;
		else if (check_for_sq(input, tmp, &con) == 0)
			continue ;
		else if (lexer_two(input, tmp, &con) == 0)
			continue ;
	}
	free(input);
	return (0);
}
