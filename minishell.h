/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:11 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/01 14:29:25 by lkonttin         ###   ########.fr       */
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
# include <string.h>
# include <errno.h>
# include "libft/include/libft.h"

typedef enum e_status
{
	FATAL,
	SYNTAX,
	ERROR,
	RUNNING,
	EXECUTE,
	CHECK
}	t_status;

typedef enum e_signal
{
	DEFAULT,
	HANDLER,
	HEREDOC,
	NO_SIGNALS
}	t_signal;

# define MALLOC "Error: malloc failed"
# define CD_FAIL ": No such file or directory"
# define PIPE "Error: error opening a pipe"
# define IS_DIR ": is a directory"
# define NO_CMD ": command not found"
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|'"
# define SYNTAX_INFILE "minishell: syntax error near unexpected token `<'"
# define SYNTAX_OUTFILE "minishell: syntax error near unexpected token `>'"
# define SYNTAX_NL "minishell: syntax error near unexpected token `newline'"
# define SYNTAX_QUOTES "minishell: syntax error with unclosed quotes"

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
	int		expands;
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
	int			heredoc_index;
	int			expand_count;
}	t_shell;

typedef struct s_parse
{
	int		i;
	int		j;
	int		k;
	char	quote;
	int		in_quotes;
	int		inside_singles;
	int		inside_doubles;
}	t_parse;

void	paths(t_shell *shell, char **envp);
char	**add_to_array(char **array, char *new);
void	remove_from_array(char **array, char *identifier);
int		copy_array(char **src, char **dst);
int		find_in_array(char **array, char *identifier);
int		array_len(char **array);
void	heredoc(t_shell *shell, t_cmd *cmd);
char	*join_n_free(char *s1, char *s2);
char	*dup_empty_str(t_shell *shell);

// INIT
void	setup_shell(t_shell *shell, char **envp);
void	setup_prompt(t_shell *shell);
void	init_tree(t_shell *shell);
void	allocate_pipes(t_shell *shell);
void	shlvl_increment(t_shell *shell);
void	init_t_parse(t_parse *p);

// PARSING

void	parse_line(t_shell *shell);
void	pipe_split(t_shell *shell, char *s);
void	tokenize(t_shell *shell, t_cmd *cmd);
int		expand(t_shell *shell, char **line);
void	extract_redirections(t_shell *shell, t_cmd *cmd);
void	extract_command(t_shell *shell, t_cmd *cmd);
void	extract_args(t_shell *shell, t_cmd *cmd);
void	replace_with_spaces(char *line, int start, int end);
void	convert_tabs_to_spaces(char *line);
int		unclosed_quotes(char *line);
void	remove_spaces(char *str);
char	*add_one_space(char *str);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);
int		ends_in_pipe(char *line);
int		starts_with_pipe(char *line);
int		invalid_pipes(t_shell *shell, char *line);
int		validate_syntax(t_shell *shell, char *s);
int		illegal_arrows(t_shell *shell, char *line, char arrow, int i);
int		only_spaces(char *line);

// BUILTINS
void	cd(t_shell *shell, t_cmd *cmd);
void	pwd(t_shell *shell, t_cmd *cmd);
void	echo(t_shell *shell, t_cmd *cmd);
void	env(t_shell *shell, int export);
void	ft_exit(t_shell *shell, t_cmd *cmd);
void	export(t_shell *shell, t_cmd *cmd);
void	unset(t_shell *shell, t_cmd *cmd);
int		builtin(t_shell *shell, t_cmd *cmd);
char	*ft_getenv(t_shell *shell, char *to_find);

// EXECUTION
void	do_fork(t_shell *shell);
void	handle_child(t_shell *shell, t_cmd *cmd_vars);
void	wait_children(t_shell *shell, int pids);
void	run_command(t_shell *shell);

// FREEING & ERROR HANDLING
void	free_pipes(t_shell *shell);
void	free_all(t_shell *shell);
void	free_tree(t_shell *shell);
void	free_array(char **array);
int		error(t_shell *shell, char *msg, t_status status, int code);
int		p_error(t_shell *shell, char *msg, t_status status, int code);

// REDIRECTION
void	redir_to_file(t_shell *shell, t_cmd *cmd_vars);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);
void	close_pipes(t_shell *shell);
void	open_pipes(t_shell *shell);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);

// SIGNALS
void	rl_replace_line(const char *text, int clear_undo);
void	toggle_signal(t_signal mode);

//debug.c
void	print_tree(t_shell *shell);
void	print_env(t_shell *shell);

#endif