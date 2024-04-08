/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:02:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/08 17:31:03 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_error(t_shell *shell, char *str)
{
	char	*error_msg;
	char	*tmp;

	tmp = ft_strjoin("minishell: exit: ", str);
	if (!tmp)
		error(shell, MALLOC, FATAL, 1);
	error_msg = ft_strjoin(tmp, ": numeric argument required\n");
	free(tmp);
	if (!error_msg)
		error(shell, MALLOC, FATAL, 1);
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
	free_all(shell);
	free_array(&shell->env);
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
		exit_error(shell, str);
	if (num == 0 && ft_strcmp(str, "0"))
		exit_error(shell, str);
	return (num);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	if (shell->parent_redir)
		restore_std(shell);
	if (isatty(STDIN_FILENO) && shell->cmd_count == 1)
		write(2, "exit\n", 5);
	if (cmd->args[1])
	{
		if (non_numeric(shell, cmd->args[1]))
			shell->exit_status = 255;
		else
			shell->exit_status = convert_to_int(shell, cmd->args[1]);
		if (cmd->args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			shell->exit_status = 1;
			return ;
		}
	}
	else
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	free_all(shell);
	free_array(&shell->env);
	toggle_signal(DEFAULT);
	exit(shell->exit_status);
}

void	free_and_exit(t_shell *shell, int status)
{
	if (shell->parent_redir)
		restore_std(shell);
	free_all(shell);
	free_array(&shell->env);
	toggle_signal(DEFAULT);
	exit(status);
}
