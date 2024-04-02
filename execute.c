/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:05 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/02 15:36:33 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_shell *shell)
{
	if (shell->status == ERROR)
		return ;
	if (shell->cmd_count == 1 && shell->cmd_tree[0].redir_count == 0)
	{
		if (builtin(shell, &shell->cmd_tree[0]))
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
	if (cmd_vars->index > 0)
		toggle_signal(NO_SIGNALS);
	else
		toggle_signal(DEFAULT);
	if (shell->cmd_count > 1)
		redir_to_pipe(shell, cmd_vars);
	if (cmd_vars->redir_count > 0)
		redir_to_file(shell, cmd_vars);
	if (!cmd_vars->cmd[0] && cmd_vars->expands > 0)
		exit(shell->exit_status);
	if (builtin(shell, cmd_vars))
		exit(shell->exit_status);
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
