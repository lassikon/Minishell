/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/27 12:44:35 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	setup_shell(&shell, envp);
	while (shell.status == RUNNING)
	{
		toggle_carret(0);
		shell.line = readline("minishell$ ");
		if (shell.line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", 2);
			exit(shell.exit_status);
		}
		toggle_carret(1);
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
	return (0);
}
