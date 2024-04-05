/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/05 12:38:58 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", 2);
			toggle_signal(DEFAULT);
			exit(shell.exit_status);
		}
		if (*shell.line)
		{
			add_history(shell.line);
			ft_putendl_fd(shell.line, shell.history_fd);
			parse_line(&shell);
			print_tree(&shell); // for debugging
			run_command(&shell);
			free_all(&shell);
		}
		shell.status = RUNNING;
	}
	close(shell.history_fd);
	toggle_signal(DEFAULT);
	return (0);
}
// exit <in (check redirection in parent process)