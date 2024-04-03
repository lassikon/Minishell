/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:02:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/03 17:25:36 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_error(t_shell *shell, char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_all(shell);
	free_array(shell->env);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(255);
}

static int	non_numeric(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			exit_error(shell, str);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	convert_to_int(t_shell *shell, char *str)
{
	int	num;

	if (!ft_strcmp(str, "9223372036854775807"))
		return (255);
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
	num = ft_atoi(str);
	if (num == -1 && ft_strcmp(str, "-1"))
	{
		exit_error(shell, str);
		return (255);
	}
	if (num == 0 && ft_strcmp(str, "0"))
	{
		exit_error(shell, str);
		return (255);
	}
	return (num);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	code;

	if (shell->parent_redir)
		restore_std(shell);
	if (isatty(STDIN_FILENO) && shell->cmd_count == 1)
		write(2, "exit\n", 5);
	if (cmd->args[1])
	{
		if (non_numeric(shell, cmd->args[1]))
			code = 255;
		else
			code = convert_to_int(shell, cmd->args[1]);
		if (cmd->args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			shell->exit_status = 1;
			return ;
		}
	}
	else
		code = WEXITSTATUS(shell->exit_status);
	free_all(shell);
	free_array(shell->env);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(code);
}

void	free_and_exit(t_shell *shell)
{
	/* int	code;

	code = WEXITSTATUS(shell->exit_status); */
	free_all(shell);
	free_array(shell->env);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(shell->exit_status);
}
