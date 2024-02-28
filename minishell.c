/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/28 16:20:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_shell *shell)
{
	int i;
	int j;

	i = 0;
	while (shell->cmd_tree[i])
	{
		j = 0;
		while (shell->cmd_tree[i][j])
		{
			free(shell->cmd_tree[i][j]);
			shell->cmd_tree[i][j] = NULL;
			j++;
		}
		free(shell->cmd_tree[i]);
		shell->cmd_tree[i] = NULL;
		i++;
	}
}

void	setup_shell(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		shell->cmd_tree[i] = NULL;
		i++;
	}
	shell->line = NULL;
	shell->status = 1;
	shell->env = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	setup_shell(&shell, envp);
	while (shell.status)
	{
		shell.line = readline("minishell$ ");
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			if (ft_strcmp(shell.line, "exit") == 0)
				shell.status = 0;
			parse_line(&shell);
			print_tree(&shell);
			// shell.status = run_command(&shell);
			free(shell.line);
			free_tree(&shell);
		}
	}
	return (0);
}
