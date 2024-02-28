/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:12:29 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/03 15:34:15 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
Parameters
lst: The address of a pointer to the first link of a list
new: The address of a pointer to the node to be added to the list

1: If the 'new' node is empty, returns NULL
2: Updates 'next' pointer of 'new' to the current head of the list
3: Updates head pointer to the 'new' node
*/