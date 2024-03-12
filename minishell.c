/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/12 15:36:44 by okarejok         ###   ########.fr       */
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
			printf("\n");
			shell.status = 0;
		}
		if (shell.line && *shell.line)
		{
			add_history(shell.line);
			ft_putendl_fd(shell.line, shell.history_fd);
			parse_line(&shell);
			print_tree(&shell); // for debugging
			run_command(&shell);
			free_tree(&shell);
			free(shell.line);
		}
		if (shell.status == ERROR)
			shell.status = RUNNING;
	}
	return (0);
}
