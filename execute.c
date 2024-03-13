/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:05 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/13 10:39:22 by lkonttin         ###   ########.fr       */
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

static void	execve_with_path(t_shell *shell, t_cmd *cmd_vars, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_one;

	i = 0;
	cmd_one = ft_strjoin("/", cmd_vars->cmd);
	if (cmd_one == NULL)
		printf("command is null!\n");
	while (shell->paths[i])
	{
		cmd_path = ft_strjoin(shell->paths[i], cmd_one);
		execve(cmd_path, cmd_vars->args, envp);
		free(cmd_path);
		i++;
	}
	free(cmd_one);
}

void	do_fork(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (parent_builtin(shell, &shell->cmd_tree[i]))
		{
			i++;
			continue ;
		}
		shell->pid[i] = fork();
		if (shell->pid[i] == -1)
		{
			waitpid(shell->pid[i -1], 0, 0);
			p_error(shell, "fork", FATAL, 1);
		}
		if (shell->pid[i] == 0)
			handle_child(shell, &shell->cmd_tree[i]);
		i++;
	}
	close_pipes(shell);
	wait_children(shell);
}

void	handle_child(t_shell *shell, t_cmd *cmd_vars)
{
	if (cmd_vars->redir_count > 0)
		redir_to_file(shell, cmd_vars);
	if (shell->cmd_count > 1)
		redir_to_pipe(shell, cmd_vars);
	if (child_builtin(shell, cmd_vars))
		exit(0);
	if (ft_strchr(cmd_vars->cmd, '/'))
	{
		if (access(cmd_vars->cmd, X_OK) == -1)
			printf("No access!\n");
		execve(cmd_vars->cmd, cmd_vars->args, shell->env);
	}
	else if (shell->paths != NULL)
	{
		execve_with_path(shell, cmd_vars, shell->env);
	}
	printf("%s failed!\n", cmd_vars->cmd);
	exit(1);
}

void	wait_children(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->pid[i], &shell->exit_status, 0);
		i++;
	}
}
