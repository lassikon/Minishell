/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:49:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/02 15:39:40 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_error_msg_strerr(char *filename)
{
	char	*msg;
	char	*temp;
	char	*error_msg;

	msg = ft_strjoin(strerror(errno), "\n");
	if (!msg)
		return (NULL);
	error_msg = ft_strjoin("minishell: ", filename);
	if (!error_msg)
	{
		free(msg);
		return (NULL);
	}
	temp = ft_strjoin(error_msg, ": ");
	if (!temp)
	{
		free(error_msg);
		free(msg);
		return (NULL);
	}
	free(error_msg);
	error_msg = join_n_free(temp, msg);
	if (!error_msg)
		return (NULL);
	return (error_msg);
}

static char	*create_error_msg(char *msg)
{
	char	*error_msg;
	char	*temp;

	if (!msg)
		return (NULL);
	temp = ft_strjoin("minishell: ", msg);
	if (!temp)
		return (NULL);
	error_msg = ft_strjoin(temp, "\n");
	if (!error_msg)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (error_msg);
}

int	error(t_shell *shell, char *msg, t_status status, int code)
{
	char	*error_msg;

	if (!msg)
		error(shell, MALLOC, FATAL, 1);
	error_msg = create_error_msg(msg);
	if (!error_msg)
		shell->status = FATAL;
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
	{
		free_all(shell);
		free_array(shell->env);
		close(shell->history_fd);
		toggle_signal(DEFAULT);
		exit(code);
	}
	return (1);
}

int	p_error(t_shell *shell, char *msg, t_status status, int code)
{
	char	*error_msg;

	error_msg = create_error_msg_strerr(msg);
	if (!error_msg)
		shell->status = FATAL;
	else
	{
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
	}
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
	{
		free_all(shell);
		free_array(shell->env);
		close(shell->history_fd);
		toggle_signal(DEFAULT);
		exit(code);
	}
	return (1);
}
