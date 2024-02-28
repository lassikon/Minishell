/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:08:21 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/17 11:14:12 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_lis
{
	char			*buf;
	struct s_lis	*next;
}	t_lis;

char	*gnl_calloc(size_t size);
t_lis	*gnl_lstlast(t_lis *list);
int		len_to_newline(t_lis *list);
char	*clean_and_free(t_lis **list, t_lis *clean_node, char *buf);
int		trim_list(t_lis **list);
char	*get_next_line(int fd);

#endif