/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:05 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/04 17:53:15 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command(t_shell *shell)
{
	open_pipes(shell);
	do_fork(shell);
}

static void	execve_with_path(t_shell *shell, char *cmd, char **envp, int index)
{
	int		i;
	char	*cmd_path;
	char	*cmd_one;

	i = 0;
	cmd_one = ft_strjoin("/", cmd);
	if (cmd_one == NULL)
		printf("command is null!\n");
	while (shell->paths[i])
	{
		cmd_path = ft_strjoin(shell->paths[i], cmd_one);
		execve(cmd_path, shell->cmd_tree[index].args, envp);
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
		shell->pid[i] = fork();
		if (shell->pid[i] == -1)
		{
			printf("FORK FAILED!\n");
			waitpid(shell->pid[i -1], 0, 0);
			exit(1);
		}
		if (shell->pid[i] == 0)
		{
			printf("i: %d cmd_index: %d\n",i, shell->cmd_tree[i].cmd_index);
			handle_child(shell, i);
		}
		i++;
	}
	close_pipes(shell);
	wait_children(shell);
}

void	handle_child(t_shell *shell, int i)
{
	if (shell->cmd_tree[i].redir_count > 0)
		redir_to_file(shell, i);
	if (shell->cmd_count > 1)
		redir_to_pipe(shell, i);
	if (ft_strchr(shell->cmd_tree[i].cmd, '/'))
	{
		if (access(shell->cmd_tree[i].cmd, X_OK) == -1)
			printf("No access!\n");
		execve(shell->cmd_tree[i].cmd, shell->cmd_tree[i].args, shell->env);
	}
	else if (shell->paths != NULL)
	{
		execve_with_path(shell, shell->cmd_tree[i].cmd, shell->env, i);
	}
	printf("%s failed!\n", shell->cmd_tree[i].cmd);
	exit(1);
}

void wait_children(t_shell *shell)
{
	int i;

	i = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->pid[i], 0, 0);
		i++;
	}
}