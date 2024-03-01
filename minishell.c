/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/01 17:58:03 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_tree(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->cmd_tree)
		return ;
	while (i < shell->cmd_count)
	{
		if (shell->cmd_tree[i].cmd)
			free(shell->cmd_tree[i].cmd);
	/* 	if (shell->cmd_tree[i].args)
			free_array(shell->cmd_tree[i].args); */
		if (shell->cmd_tree[i].redir)
			free_array(shell->cmd_tree[i].redir, shell->cmd_tree[i].redir_count);
		i++;
	}
	free(shell->cmd_tree);
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
			else
			{
				parse_line(&shell);
				print_tree(&shell); // for debugging
				// shell.status = run_command(&shell);
				free_tree(&shell);
			}
			free(shell.line);
		}
	}
	return (0);
}
