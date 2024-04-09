/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:10:31 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/09 16:58:19 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell *shell)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	free_array(&shell->env);
	free_all(shell);
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
			parse_line(&shell);
			run_command(&shell);
			free_all(&shell);
		}
		else
			free(shell.line);
		shell.status = RUNNING;
	}
	exit_shell(&shell);
}
