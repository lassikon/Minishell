/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:49:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/08 15:22:04 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(t_shell *shell, char *msg, t_status status, int code)
{
	char	*error_msg;

	if (shell->parent_redir)
		restore_std(shell);
	if (!msg)
		free_and_exit(shell, 1);
	error_msg = create_error_msg(msg);
	if (!error_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}

int	p_error(t_shell *shell, char *msg, t_status status, int code)
{
	char	*error_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	error_msg = create_error_msg_strerr(msg);
	if (!error_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}

int	child_perror(t_shell *shell, char *msg, t_status status, int code)
{
	char	*error_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	error_msg = create_error_msg_strerr(msg);
	if (!error_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	free(msg);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}

int	child_error(t_shell *shell, char *msg, t_status status, int code)
{
	char	*error_msg;

	if (!msg)
		free_and_exit(shell, 1);
	if (shell->parent_redir)
		restore_std(shell);
	error_msg = create_error_msg(msg);
	if (!error_msg)
		free_and_exit(shell, 1);
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	free(msg);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
		free_and_exit(shell, code);
	return (1);
}
