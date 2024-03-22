/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/22 16:36:08 by okarejok         ###   ########.fr       */
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
	toggle_carret(0);
	while (shell.status == RUNNING)
	{
		shell.line = readline("minishell$ ");
		if (shell.line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", 2);
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
	return (0);
}
