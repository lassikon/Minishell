/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:11 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/11 14:44:05 by lkonttin         ###   ########.fr       */
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
# include <termios.h>
# include "libft/include/libft.h"

typedef enum e_error
{
	FATAL,
	SYNTAX
} t_error;

typedef struct s_cmd
{
	char	*line; // raw input string to be parsed
	char	*cmd;
	char	**args;
	char	**redir; // array of <, >, >> or << + filename/LIM
	// int		heredoc_count;
	int		redir_count;
	int		infile;
	int		outfile;
	int		index;
	int		arg_count;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*line;
	char	**pipe_split;
	t_cmd	*cmd_tree;
	char	**paths;
	int		cmd_count;
	int		line_len;
	int		status;
	int		exit_status;
	int		pid[1024];
	int		pipe[1024][2];
}	t_shell;

void	parse_line(t_shell *shell);
void	setup_shell(t_shell *shell, char **envp);
void	init_tree(t_shell *shell);
void	check_expands(t_shell *shell, t_cmd *cmd);
int		extract_redirections(t_shell *shell, t_cmd *cmd);
void	extract_command(t_shell *shell, t_cmd *cmd);
void	extract_args(t_shell *shell, t_cmd *cmd);
void	delete_from_line(char *line, int start, int end);
int		check_unclosed_quotes(char *line);
void	remove_spaces(char *str);
char	*add_one_space(char *str);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);
void    do_fork(t_shell *shell);
void    handle_child(t_shell *shell, t_cmd *cmd_vars);
void    redir_to_file(t_shell *shell, t_cmd *cmd_vars);
void    redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);
void	wait_children(t_shell *shell);
void	paths(t_shell *shell, char **envp);
void 	close_pipes(t_shell *shell);
void 	open_pipes(t_shell *shell);
void    run_command(t_shell *shell);
void	child_builtin(t_shell *shell, t_cmd *cmd);
int		parent_builtin(t_shell *shell, t_cmd *cmd);
char	**add_to_array(char **array, char *new);
void	remove_from_array(char **array, char *identifier);
int		copy_array(char **src, char **dst);
int		find_in_array(char **array, char *identifier);
int		array_len(char **array);
void	free_array(char **array);
void	cd(t_shell *shell, t_cmd *cmd);
void	pwd(t_shell *shell, t_cmd *cmd);
void	echo(t_shell *shell, t_cmd *cmd);
void	env(t_shell *shell);
void	ft_exit(t_shell *shell, t_cmd *cmd);
char	*find_home_dir(t_shell *shell);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);
void	heredoc(t_shell *shell, t_cmd *cmd);
char	*join_n_free(char *s1, char *s2);
void	signal_handler(int signal);
void    rl_replace_line (const char *text, int clear_undo);
//debug.c
void	print_tree(t_shell *shell);
void	print_env(t_shell *shell);
void	toggle_carret(int is_on);

#endif