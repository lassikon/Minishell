/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:49:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/28 12:19:08 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(t_shell *shell, char *msg, t_status status, int code)
{
	ft_putendl_fd(msg, 2);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
	{
		free_all(shell);
		free_array(shell->env);
		close(shell->history_fd);
		exit(code);
	}
	return (1);
}

int	p_error(t_shell *shell, char *msg, t_status status, int code)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
	{
		free_all(shell);
		free_array(shell->env);
		close(shell->history_fd);
		exit(code);
	}
	return (1);
}
