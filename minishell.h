/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:11 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/10 14:34:50 by lkonttin         ###   ########.fr       */
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
	EXPORT,
	UNSET,
	FREEABLE
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
# define GETCWD "Error: getcwd failed"
# define SYNTAX_PIPE "syntax error near unexpected token `|'"
# define SYNTAX_INFILE "syntax error near unexpected token `<'"
# define SYNTAX_OUTFILE "syntax error near unexpected token `>'"
# define SYNTAX_NL "syntax error near unexpected token `newline'"
# define SYNTAX_QUOTES "syntax error with unclosed quotes"

typedef struct s_cmd
{
	char	*line;
	char	*cmd;
	char	**args;
	char	**redir;
	int		redir_count;
	int		infile;
	int		out;
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
	t_status	status;
	int			exit_status;
	int			*pid;
	int			pid_allocated;
	int			**pipe;
	int			pipes_allocated;
	int			heredoc_index;
	int			std_in;
	int			std_out;
	int			parent_redir;
	char		*pwd;
	char		*old_pwd;
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

// INIT
void	setup_shell(t_shell *shell, char **envp);
void	setup_prompt(t_shell *shell);
void	init_tree(t_shell *shell);
void	allocate_pipes(t_shell *shell);
void	shlvl_increment(t_shell *shell);
void	init_t_parse(t_parse *p);

// SIGNALS
void	rl_replace_line(const char *text, int clear_undo);
void	toggle_signal(t_signal mode);

// PARSING
void	parse_line(t_shell *shell);
void	mark_actual_pipes(char *s);
void	expand(t_shell *shell, char **line);
void	extract_redirections(t_shell *shell, t_cmd *cmd);
void	extract_command(t_shell *shell, t_cmd *cmd);
void	extract_args(t_shell *shell, t_cmd *cmd);
int		ends_in_pipe(char *line);
int		starts_with_pipe(char *line);
int		invalid_pipes(t_shell *shell, char *line);
int		illegal_arrows(t_shell *shell, char *line, char arrow, int i);
int		only_spaces(char *line);
void	replace_with_spaces(char *line, int start, int end);
void	convert_tabs_to_spaces(char *line);
int		unclosed_quotes(char *line);
void	remove_spaces(char *str);
char	*add_one_space(char *str);
int		skip_quotes(char *line, int i);
void	remove_quotes(char *str);

// BUILTINS
void	cd(t_shell *shell, t_cmd *cmd);
void	pwd(t_shell *shell, t_cmd *cmd);
void	echo(t_shell *shell, t_cmd *cmd);
void	env(t_shell *shell);
void	ft_exit(t_shell *shell, t_cmd *cmd);
void	export(t_shell *shell, t_cmd *cmd);
void	unset(t_shell *shell, t_cmd *cmd);
int		run_builtin(t_shell *shell, t_cmd *cmd);
int		check_builtin(t_cmd *cmd);
char	*ft_getenv(t_shell *shell, char *to_find);
int		exists_in_env(char **env, char *identifier);

// EXECUTION
void	do_fork(t_shell *shell);
void	handle_child(t_shell *shell, t_cmd *cmd_vars);
void	wait_children(t_shell *shell, int pids);
void	run_command(t_shell *shell);
void	validate_command(t_shell *shell, t_cmd *cmd_vars);

// REDIRECTION
void	redir_to_file(t_shell *shell, t_cmd *cmd_vars, t_status mode);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);
void	close_pipes(t_shell *shell);
void	open_pipes(t_shell *shell);
void	redir_to_pipe(t_shell *shell, t_cmd *cmd_vars);
void	restore_std(t_shell *shell);
void	heredoc(t_shell *shell, t_cmd *cmd);

// FREEING & ERROR HANDLING
void	free_pipes(t_shell *shell);
void	free_all(t_shell *shell);
void	free_tree(t_shell *shell);
void	free_array(char ***array);
void	export_error_msg(t_shell *shell, char *arg, t_status type);
int		error(t_shell *shell, char *msg, t_status status, int code);
int		p_error(t_shell *shell, char *msg, t_status status, int code);
int		child_error(t_shell *shell, char *msg, t_status status, int code);
void	free_and_exit(t_shell *shell, int status);
void	cd_error(t_shell *shell, char *path);
char	*create_error_msg_strerr(char *filename);
char	*create_error_msg(char *msg);
void	malloc_error(t_shell *shell, char *str, t_status status);

// GENERAL UTILS
void	paths(t_shell *shell, char **envp);
char	**add_to_array(t_shell *shell, char **array, char *new, t_status mode);
void	remove_from_array(char **array, char *identifier);
char	**copy_array(t_shell *shell, char **array);
int		find_in_array(char **array, char *identifier);
int		array_len(char **array);
char	*join_n_free(char *s1, char *s2);
char	*dup_empty_str(t_shell *shell);

#endif