/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:11 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/21 12:44:02 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "libft/include/libft.h"

typedef enum e_status
{
	FATAL,
	SYNTAX,
	ERROR,
	RUNNING
} t_status;

# define MALLOC "Error: malloc failed"
# define CD_FAIL ": No such file or directory"
# define PIPE "Error: error opening a pipe"
# define IS_DIR ": is a directory"
# define SYNTAX_PIPE "syntax error near unexpected token `|'"
# define QUOTES "Error: unclosed quotes"

typedef struct s_cmd
{
	char	*line; // raw input string to be parsed
	char	*cmd;
	char	**args;
	char	**redir; // array of <, >, >> or << + filename/LIM
	int		redir_count;
	int		infile;
	int		outfile;
	int		index;
	int		arg_count;
}	t_cmd;

typedef struct s_shell
{
	char		**env;
	char		*line;
	t_cmd		*cmd_tree;
	char		**paths;
	int			cmd_count;
	int			line_len;
	t_status	status;
	int			exit_status;
	int			*pid;
	int			**pipe;
	int			history_fd;
}	t_shell;

void	paths(t_shell *shell, char **envp);
char	**add_to_array(char **array, char *new);
void	remove_from_array(char **array, char *identifier);
int		copy_array(char **src, char **dst);
int		find_in_array(char **array, char *identifier);
int		array_len(char **array);
void	heredoc(t_shell *shell, t_cmd *cmd);
char	*join_n_free(char *s1, char *s2);

// INIT
void	setup_shell(t_shell *shell, char **envp);
void	setup_prompt(t_shell *shell);
void	init_tree(t_shell *shell);
void	allocate_pipes(t_shell *shell);

// PARSING

void	parse_line(t_shell *shell);
void	pipe_split(t_shell *shell, char *s);
void	tokenize(t_shell *shell, t_cmd *cmd);
void	check_expands(t_shell *shell, char **line);
int		extract_redirections(t_shell *shell, t_cmd *cmd);
void	extract_command(t_shell *shell, t_cmd *cmd);
void	extract_args(t_shell *shell, t_cmd *cmd);
void	replace_with_spaces(char *line, int start, int end);
int		check_unclosed_quotes(char *line);
void	remove_spaces(char *str);
char	*add_one_space(char *str);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);

// BUILTINS
void	cd(t_shell *shell, t_cmd *cmd);
void	pwd(t_shell *shell, t_cmd *cmd);
void	echo(t_shell *shell, t_cmd *cmd);
void	env(t_shell *shell, int export);
void	ft_exit(t_shell *shell, t_cmd *cmd);
void	export(t_shell *shell, t_cmd *cmd);
int		child_builtin(t_shell *shell, t_cmd *cmd);
int		parent_builtin(t_shell *shell, t_cmd *cmd);
char	*ft_getenv(t_shell *shell, char *to_find);

// EXECUTION
void	do_fork(t_shell *shell);
void	handle_child(t_shell *shell, t_cmd *cmd_vars);
void	wait_children(t_shell *shell);
void	run_command(t_shell *shell);

// FREEING & ERROR HANDLING
void	free_pipes(t_shell *shell);
void	free_all(t_shell *shell);
void	free_tree(t_shell *shell);
void	free_array(char **array);
void	error(t_shell *shell, char *msg, t_status status, int code);
void	p_error(t_shell *shell, char *msg, t_status status, int code);

// REDIRECTION
void	redir_to_file(t_shell *shell, t_cmd *cmd_vars);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);
void	close_pipes(t_shell *shell);
void	open_pipes(t_shell *shell);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);

// SIGNALS
void	signal_handler(int signal);
void	rl_replace_line(const char *text, int clear_undo);
void	toggle_carret(int is_on);

//debug.c
void	print_tree(t_shell *shell);
void	print_env(t_shell *shell);

#endif