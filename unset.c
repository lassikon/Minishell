/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:40:22 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/05 16:41:23 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_unset_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	unset(t_shell *shell, t_cmd *cmd)
{
	char	*identifier;
	int		i;

	i = 1;
	if (!cmd->args[i])
		return ;
	while (cmd->args[i])
	{
		if (invalid_unset_identifier(cmd->args[i]))
			export_error_msg(shell, cmd->args[i], UNSET);
		else
		{
			identifier = ft_strjoin(cmd->args[i], "=");
			if (identifier == NULL)
				error(shell, MALLOC, FATAL, 1);
			if (find_in_array(shell->env, identifier))
				remove_from_array(shell->env, identifier);
			free(identifier);
		}
		i++;
	}
}
