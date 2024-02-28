/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:11 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/28 16:21:23 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/include/libft.h"

typedef struct s_shell
{
	char	**env;
	char	*line;
	char	**pipe_split;
	char	**cmd_tree[10];
	int		status;
}	t_shell;

void	parse_line(t_shell *shell);

//debug.c
void	print_tree(t_shell *shell);

#endif