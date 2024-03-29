/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:02:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/29 12:45:28 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static int	non_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			exit_error(str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	convert_to_int(char *str)
{
	int	num;

	if (!ft_strcmp(str, "9223372036854775807"))
		return (255);
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
	num = ft_atoi(str);
	if (num == -1 && ft_strcmp(str, "-1"))
	{
		exit_error(str);
		return (255);
	}
	if (num == 0 && ft_strcmp(str, "0"))
	{
		exit_error(str);
		return (255);
	}
	return (num);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 2);
	if (cmd->arg_count > 2)
	{
		error(shell, "minishell: exit: too many arguments", ERROR, 1);
		return ;
	}
	if (cmd->arg_count == 2)
	{
		if (non_numeric(cmd->args[1]))
			code = 255;
		else
			code = convert_to_int(cmd->args[1]);
	}
	else
		code = WEXITSTATUS(shell->exit_status);
	free_all(shell);
	free_array(shell->env);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(code);
}
