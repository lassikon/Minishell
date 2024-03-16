/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:49:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/16 13:42:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_shell *shell, char *msg, t_status status, int code)
{
	// ft_putstr_fd("minishell: error: ", 2);
	ft_putendl_fd(msg, 2);
	//free_all(shell);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
	{
		free_array(shell->env);
		exit(code);
	}
}

void	p_error(t_shell *shell, char *msg, t_status status, int code)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	free_all(shell);
	shell->status = status;
	shell->exit_status = code;
	if (shell->status == FATAL)
	{
		free_array(shell->env);
		exit(code);
	}
}
