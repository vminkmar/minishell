/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:38:34 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/05 22:30:34 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
	{
		return (0);
	}
	return (1);
}

char	*stupid_shit( char *s1, char *s2, int *i, int *j)
{
	size_t	c;
	size_t	d;
	char	*a;

	*j = 0;
	*i = 0;
	c = ft_strlen(s1);
	d = ft_strlen(s2);
	a = malloc((c + d) * sizeof(char) + 1);
	if (a == NULL)
		return (NULL);
	return (a);
}

char	*sl_strjoin(char *s1, char *s2)
{
	char	*a;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (NULL);
	a = stupid_shit(s1, s2, &i, &j);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i ++;
	}
	if (s2[j] == '\0')
	{
		return (a[i] = '\0', a);
	}
	while (s2[j] != '\0')
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	return (a[i] = '\0', a);
}
