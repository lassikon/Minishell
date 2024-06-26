/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:51 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/08 15:52:07 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_space(t_shell *shell)
{
	char	*str;

	str = ft_strdup(" ");
	if (!str)
		error(shell, MALLOC, FATAL, 1);
	return (str);
}

static char	*dup_newline(t_shell *shell)
{
	char	*str;

	str = ft_strdup("\n");
	if (!str)
		error(shell, MALLOC, FATAL, 1);
	return (str);
}

static char	*create_output(t_shell *shell, t_cmd *cmd, int i)
{
	char	*temp;
	char	*output;

	output = NULL;
	while (cmd->args[i])
	{
		temp = ft_strdup(cmd->args[i]);
		if (!temp)
			error(shell, MALLOC, FATAL, 1);
		if (cmd->args[i + 1])
		{
			temp = join_n_free(temp, dup_space(shell));
			if (!temp)
				error(shell, MALLOC, FATAL, 1);
		}
		output = join_n_free(output, temp);
		if (!output)
			error(shell, MALLOC, FATAL, 1);
		i++;
	}
	return (output);
}

static int	check_flag(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		if (ft_strncmp(cmd->args[i], "-n", 2) == 0)
		{
			j = 1;
			while (cmd->args[i][j] && cmd->args[i][j] == 'n')
				j++;
			if (cmd->args[i][j])
				return (i);
		}
		i++;
	}
	return (i - 1);
}

void	echo(t_shell *shell, t_cmd *cmd)
{
	char	*output;

	if (!cmd->args[1])
	{
		write(1, "\n", 1);
		if (shell->status != ERROR)
			shell->exit_status = 0;
		return ;
	}
	if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
	{
		output = create_output(shell, cmd, check_flag(cmd));
	}
	else
	{
		output = create_output(shell, cmd, 1);
		output = join_n_free(output, dup_newline(shell));
		if (!output)
			error(shell, MALLOC, FATAL, 1);
	}
	write(1, output, ft_strlen(output));
	free(output);
	if (shell->status != ERROR)
		shell->exit_status = 0;
}
