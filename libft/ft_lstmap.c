/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:30:35 by vminkmar          #+#    #+#             */
/*   Updated: 2022/04/25 18:02:17 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp_l;

	tmp_l = NULL;
	if (f == NULL || lst == NULL)
		return (NULL);
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == NULL)
		{
			ft_lstclear(&tmp_l, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&tmp_l, tmp);
	}
	return (tmp_l);
}
