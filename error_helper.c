/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:02:01 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/08 15:43:58 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error_msg(t_shell *shell, char *arg, t_status type)
{
	char	*error_msg;
	char	*temp;

	if (type == EXPORT)
		temp = ft_strjoin("export: `", arg);
	else if (type == UNSET)
		temp = ft_strjoin("unset: `", arg);
	else
		return ;
	if (temp == NULL)
		error(shell, MALLOC, FATAL, 1);
	error_msg = ft_strjoin(temp, "': not a valid identifier");
	free(temp);
	if (error_msg == NULL)
		error(shell, MALLOC, FATAL, 1);
	error(shell, error_msg, ERROR, 1);
	free(error_msg);
}

char	*create_error_msg_strerr(char *filename)
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

char	*create_error_msg(char *msg)
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
