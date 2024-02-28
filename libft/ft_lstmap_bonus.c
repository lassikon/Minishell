/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:55:08 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/07 12:23:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*first_node;
	t_list	*temp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	first_node = NULL;
	while (lst != NULL)
	{
		temp = f(lst->content);
		new = ft_lstnew(temp);
		if (new == NULL)
		{
			del(temp);
			ft_lstclear(&first_node, del);
			return (NULL);
		}
		ft_lstadd_back(&first_node, new);
		lst = lst->next;
	}
	return (first_node);
}
