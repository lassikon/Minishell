/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:17:51 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/03 16:23:10 by okarejok         ###   ########.fr       */
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

	output = ft_calloc(1, 1);
	if (!output)
		error(shell, MALLOC, FATAL, 1);
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
		output = create_output(shell, cmd, 2);
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
