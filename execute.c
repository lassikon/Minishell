/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:05 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/03 17:27:27 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std(t_shell *shell)
{
	dup2(shell->std_in, STDIN_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	close(shell->std_in);
	close(shell->std_out);
	shell->parent_redir = 0;
}

void	run_command(t_shell *shell)
{
	if (shell->status == ERROR)
		return ;
	if (shell->cmd_count == 1 && check_builtin(&shell->cmd_tree[0]))
	{
		if (shell->cmd_tree[0].redir_count > 0)
		{
			shell->parent_redir = 1;
			shell->std_in = dup(STDIN_FILENO);
			shell->std_out = dup(STDOUT_FILENO);
			redir_to_file(shell, &shell->cmd_tree[0], ERROR);
		}
		if (shell->status != ERROR)
			run_builtin(shell, &shell->cmd_tree[0]);
		if (shell->parent_redir)
			restore_std(shell);
		return ;
	}
	if (shell->cmd_count > 1)
		open_pipes(shell);
	do_fork(shell);
}

void	do_fork(t_shell *shell)
{
	int	i;

	i = 0;
	toggle_signal(NO_SIGNALS);
	while (i < shell->cmd_count)
	{
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
	if (shell->cmd_count > 1)
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
		redir_to_file(shell, cmd_vars, FATAL);
	if (cmd_vars->cmd == NULL)
		exit(shell->exit_status);
	if (run_builtin(shell, cmd_vars))
		exit(shell->exit_status);
	if (cmd_vars->cmd[0])
		validate_command(shell, cmd_vars);
	execve(cmd_vars->cmd, cmd_vars->args, shell->env);
	error(shell, ft_strjoin(cmd_vars->cmd, NO_CMD), FATAL, 127);
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
