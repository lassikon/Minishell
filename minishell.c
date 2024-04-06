/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/06 19:51:25 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell *shell)
{
	// write(2, "exiting shell\n", 14);
	free_array(&shell->env);
	free_all(shell);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	setup_shell(&shell, envp);
	toggle_signal(HANDLER);
	while (shell.status == RUNNING)
	{
		shell.line = readline("minishell$ ");
		if (shell.line == NULL)
			exit_shell(&shell);
		if (*shell.line)
		{
			add_history(shell.line);
			ft_putendl_fd(shell.line, shell.history_fd);
			// write(2, "parsing line\n", 13);
			parse_line(&shell);
			// print_tree(&shell); // for debugging
			// write(2, "running command\n", 16);
			run_command(&shell);
			// write(2, "freeing all\n", 12);
			free_all(&shell);
			// write(2, "freed all\n", 10);
		}
		shell.status = RUNNING;
	}
	exit_shell(&shell);
}
