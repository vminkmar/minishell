/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_get_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:06:51 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 13:35:20 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_words_with_dollar_and_quotes(char *str, t_sup *sup)
{
	if ((str[sup->i] == '$' && str[sup->i + 1] == '\"')
		|| (str[sup->i] == '$' && str[sup->i + 1] == '\''))
	{
		sup->j = sup->i;
		sup->i += 2;
		if (str[sup->i - 1] == '\'')
			while (str[sup->i] != '\'' && str[sup->i] != '\0')
				(sup->i)++;
		else
			while (str[sup->i] != '\"' && str[sup->i] != '\0')
				(sup->i)++;
		sup->value[sup->words] = ft_substr(str, sup->j, sup->i + 1 - sup->j);
		sup->words ++;
		sup->j = sup->i;
	}
}

void	get_words_with_dollar_question_mark(char *str, t_sup *sup, int length)
{
	if (str[sup->i] == '$' && str[sup->i + 1] == '?')
	{
		sup->j = sup->i;
		sup->i += 2;
		while (is_valid(str[sup->i]) == 0 && sup->i < length)
			sup->i++;
		sup->value[sup->words] = ft_substr(str, sup->j, sup->i - sup->j);
		sup->words ++;
		sup->j = sup->i;
	}
}

void	get_words_with_dollar(char *str, t_sup *sup, int length)
{
	if (str[sup->i] == '$')
	{
		sup->j = sup->i;
		sup->i ++;
		while (is_valid(str[sup->i]) == 0 && sup->i < length)
			sup->i++;
		sup->value[sup->words] = ft_substr(str, sup->j, sup->i - sup->j);
		sup->words ++;
		sup->j = sup->i;
	}
}

void	get_words_variable(char *str, t_sup *sup, int length)
{
	while (str[sup->i] != '$' && sup->i < length)
	{
		if (str[sup->i + 1] == '$')
		{
			sup->value[sup->words] = ft_substr(str, sup->j, sup->i + 1 - sup->j);
			sup->j = sup->i;
			sup->words ++;
		}
		else if (sup->i + 1 == length)
		{
			sup->value[sup->words] = ft_substr(str, sup->j, sup->i + 1
					- sup->j);
			sup->j = sup->i;
			sup->words ++;
		}
		sup->i++;
	}
}

char	**get_words(char *str, int length, int counter, t_sup *sup)
{
	sup->words = 0;
	sup->i = 0;
	sup->j = 0;
	sup->value = malloc((counter + 1) * sizeof(char *));
	if (sup->value == NULL)
	{
		printf("memory allocation failed");
		return (NULL);
	}
	while (sup->i < length)
	{
		get_words_with_dollar_and_quotes(str, sup);
		get_words_with_dollar_question_mark(str, sup, length);
		get_words_with_dollar(str, sup, length);
		get_words_variable(str, sup, length);
	}
	sup->value[sup->words] = NULL;
	return (sup->value);
}
