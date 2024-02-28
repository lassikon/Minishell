/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:11:20 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/03 10:11:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*root;

	root = malloc(sizeof(t_list));
	if (root == NULL)
		return (NULL);
	root->content = content;
	root->next = NULL;
	return (root);
}
/*
Parameters
content: The content to create the node with

1: Allocates memory for a new node, returns NULL if allocation fails
2: Sets 'content' member with the data provided as function argument
3: Sets 'next' pointer to NULL
4: Returns pointer to the node
*/