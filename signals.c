/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:46:08 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/10 11:08:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

static void	toggle_caret(int is_on)
{
	struct termios	new_attr;

	tcgetattr(STDIN_FILENO, &new_attr);
	if (!is_on)
		new_attr.c_lflag &= ~ECHOCTL;
	else
		new_attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}

void	toggle_signal(t_signal mode)
{
	if (mode == DEFAULT)
	{
		toggle_caret(1);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == HANDLER)
	{
		toggle_caret(0);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_handler);
	}
	else if (mode == NO_SIGNALS)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
