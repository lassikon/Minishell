/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:46:08 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/11 16:04:11 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		rl_redisplay();
}

static void	sigquit_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		ctrl_c_handler(signal);
	if (signal == SIGQUIT)
		sigquit_handler(signal);
}

void	toggle_carret(int is_on)
{
	struct termios	new_attr;

	tcgetattr(STDIN_FILENO, &new_attr);
	if (!is_on)
		new_attr.c_lflag &= ~ECHOCTL;
	else
		new_attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}
