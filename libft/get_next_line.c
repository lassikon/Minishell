/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:15:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/17 12:05:06 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	found_newline(t_lis *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->buf[i] && i < BUFFER_SIZE)
		{
			if (list->buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

static void	copy_str(t_lis *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buf[i] != '\0')
		{
			if (list->buf[i] == '\n')
			{
				str[k] = '\n';
				str[k + 1] = '\0';
				return ;
			}
			str[k++] = list->buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

static int	add_to_list(t_lis **list, char *buf)
{
	t_lis	*new_node;
	t_lis	*last_node;

	last_node = gnl_lstlast(*list);
	new_node = malloc(sizeof(t_lis));
	if (new_node == NULL)
		return (0);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->buf = buf;
	new_node->next = NULL;
	return (1);
}

static int	create_list(t_lis **list, int fd)
{
	int		bytes_read;
	char	*buf;

	bytes_read = 0;
	while (!found_newline(*list))
	{
		buf = gnl_calloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (0);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			free(buf);
			return (1);
		}
		if (!(add_to_list(list, buf)) || bytes_read < 0)
		{
			free(buf);
			return (0);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_lis	*list = NULL;
	char			*line;
	int				str_len;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (clean_and_free(&list, 0, line));
	if (!(create_list(&list, fd)))
		return (clean_and_free(&list, 0, line));
	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	line = gnl_calloc(str_len + 1);
	if (line == NULL)
		return (clean_and_free(&list, 0, line));
	copy_str(list, line);
	if (!(trim_list(&list)))
		return (clean_and_free(&list, 0, line));
	return (line);
}
