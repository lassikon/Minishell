/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:11 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/01 17:40:21 by lkonttin         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*line; // raw input string to be parsed
	char	*cmd;
	char	**args;
	char	**redir; // array of <, >, >> or << + filename
	int		redir_count;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*line;
	char	**pipe_split;
	t_cmd	*cmd_tree;
	int		cmd_count;
	int		line_len;
	int		status;
}	t_shell;

void	parse_line(t_shell *shell);
void	setup_shell(t_shell *shell, char **envp);
void	init_tree(t_shell *shell);
void	extract_redirections(t_shell *shell, t_cmd *cmd);

//debug.c
void	print_tree(t_shell *shell);

#endif