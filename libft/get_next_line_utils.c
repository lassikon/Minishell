/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:53:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/17 12:08:28 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_calloc(size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

t_lis	*gnl_lstlast(t_lis *list)
{
	while (list != NULL)
	{
		if (list->next == NULL)
			return (list);
		list = list->next;
	}
	return (list);
}

int	len_to_newline(t_lis *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buf[i] != '\0')
		{
			if (list->buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

int	trim_list(t_lis **list)
{
	t_lis	*last_node;
	t_lis	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = gnl_calloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (0);
	clean_node = malloc(sizeof(t_lis));
	if (clean_node == NULL)
		return (free(buf), 0);
	last_node = gnl_lstlast(*list);
	i = 0;
	k = 0;
	while (last_node->buf[i] && last_node->buf[i] != '\n')
		++i;
	while (last_node->buf[i] && last_node->buf[++i])
		buf[k++] = last_node->buf[i];
	clean_node->buf = buf;
	clean_node->next = NULL;
	clean_and_free(list, clean_node, buf);
	return (1);
}

char	*clean_and_free(t_lis **list, t_lis *clean_node, char *buf)
{
	t_lis	*temp;

	if (*list == NULL)
		return (NULL);
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node == 0 || buf == 0)
	{
		free(buf);
		return (NULL);
	}
	if (clean_node->buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
	return (NULL);
}
