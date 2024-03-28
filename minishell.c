/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/28 14:51:25 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	(void)argc;
	(void)argv;
	setup_shell(&shell, envp);
	while (shell.status == RUNNING)
	{
		toggle_signal(HANDLER);
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
			// print_tree(&shell); // for debugging
			run_command(&shell);
			free_all(&shell);
		}
		shell.status = RUNNING;
	}
	close(shell.history_fd);
	toggle_signal(DEFAULT);
	return (0);
}
// fix quotes handling (like "l""s" etc) (arg count is wrong too)
// exit <in (check redirection in parent process)
// naked expands can lead to segfault
// unset needs to check identifier validity