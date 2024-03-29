/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:05 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/29 11:44:28 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_shell *shell)
{
	if (shell->status == ERROR)
		return ;
	open_pipes(shell);
	do_fork(shell);
}

int	absolute_path_to_directory(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}

static int check_cmd_path(t_shell *shell, t_cmd *cmd_vars)
{
	int		i;
	char	*cmd_path;
	char	*cmd_one;

	i = 0;
	cmd_one = ft_strjoin("/", cmd_vars->cmd);
	if (cmd_one == NULL)
		error(shell, MALLOC, FATAL, 1);
	while (shell->paths[i])
	{
		cmd_path = ft_strjoin(shell->paths[i], cmd_one);
		if (!cmd_path)
			error(shell, MALLOC, FATAL, 1);
		if (absolute_path_to_directory(cmd_path))
		{
			free(cmd_path);
			i++;
			continue ;
		}
		if (access(cmd_path, 0) == 0)
		{
			if (access(cmd_path, X_OK) == -1)
				return (p_error(shell, cmd_path, ERROR, 126));
			cmd_vars->cmd = cmd_path;
			return (0);
		}
		free(cmd_path);
		i++;
	}
	free(cmd_one);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_vars->cmd, 2);
	return (error(shell, NO_CMD, ERROR, 127));
}

static int	validate_command(t_shell *shell, t_cmd *cmd_vars)
{
	if (cmd_vars->cmd[0] == '\0')
		return (0);
	if (child_builtin(shell, cmd_vars, CHECK))
		return (0);
	if (ft_strchr(cmd_vars->cmd, '/'))
	{
		if (access(cmd_vars->cmd, F_OK) == -1)
			return (p_error(shell, cmd_vars->cmd, ERROR, 127));
		else if (access(cmd_vars->cmd, X_OK) == -1)
			return (p_error(shell, cmd_vars->cmd, ERROR, 126));
		if (absolute_path_to_directory(cmd_vars->cmd))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_vars->cmd, 2);
			return (error(shell, IS_DIR, ERROR, 126));
		}
	}
	else
	{
		if (shell->paths != NULL)
			return (check_cmd_path(shell, cmd_vars));
	}
	return (0);
}

void	do_fork(t_shell *shell)
{
	int	i;

	i = 0;
	toggle_signal(NO_SIGNALS);
	while (i < shell->cmd_count)
	{
		if (parent_builtin(shell, &shell->cmd_tree[i])
			|| validate_command(shell, &shell->cmd_tree[i]))
		{
			i++;
			continue ;
		}
		shell->pid[i] = fork();
		if (shell->pid[i] == -1)
		{
			wait_children(shell, i);
			p_error(shell, "fork", FATAL, 1);
		}
		if (shell->pid[i] == 0)
			handle_child(shell, &shell->cmd_tree[i]);
		i++;
	}
	close_pipes(shell);
	wait_children(shell, shell->cmd_count);
	toggle_signal(HANDLER);
}

void	handle_child(t_shell *shell, t_cmd *cmd_vars)
{
	toggle_signal(DEFAULT);
	if (shell->cmd_count > 1)
		redir_to_pipe(shell, cmd_vars);
	if (cmd_vars->redir_count > 0)
		redir_to_file(shell, cmd_vars);
	if (!cmd_vars->cmd[0])
		exit(shell->exit_status);
	if (child_builtin(shell, cmd_vars, EXECUTE))
		exit(shell->exit_status);
	execve(cmd_vars->cmd, cmd_vars->args, shell->env);
	write(2, "minishell: execve failed\n", 25);
	exit(127);
}

int	no_children(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (shell->pid[i] > 0)
			return (0);
		i++;
	}
	return (1);
}

void	wait_children(t_shell *shell, int pids)
{
	int	i;

	if (no_children(shell))
		return ;
	i = 0;
	while (i < pids)
	{
		waitpid(shell->pid[i], &shell->exit_status, 0);
		if (WIFSIGNALED(shell->exit_status))
		{
			if (WTERMSIG(shell->exit_status) == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			else if (WTERMSIG(shell->exit_status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
		if (!WIFEXITED(shell->exit_status))
			shell->exit_status = 1;
		i++;
	}
}
