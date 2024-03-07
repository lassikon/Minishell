/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:11:41 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/07 10:22:46 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_env(t_shell *shell, char **line, int i)
{
	int		start;
	int		end;
	char	*value;
	char	*env;
	char	*new;

	(void)shell;
	start = i;
	i++;
	if ((*line)[i] == '?')
	{
		i++;
		end = i;
		value = ft_itoa(shell->exit_status);
	}
	else
	{
		while ((*line)[i] && ft_isalnum((*line)[i]))
			i++;
		end = i;
		env = ft_substr(*line, start + 1, end - start - 1);
		value = getenv(env);
		free(env);
		if (!value)
			value = "";
	}
	new = ft_strjoin(ft_substr(*line, 0, start), value);
	new = ft_strjoin(new, ft_substr(*line, end, ft_strlen(*line) - end));
	*line = new;
	return (start + ft_strlen(value));
}

void	check_expands(t_shell *shell, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'')
		{
			i = skip_quotes(cmd->line, i);
		}
		if (cmd->line[i] == '$')
		{
			i = expand_env(shell, &cmd->line, i);
		}
		if (cmd->line[i] == '*')
		{
			// handle wildcard
		}
		i++;
	}
}
