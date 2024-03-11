/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:11:41 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/11 16:00:48 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fetch_env(t_shell *shell, char *line, int *i)
{
	int		start;
	int		end;
	char	*env;
	char	*value;

	printf("fetch_env\n");
	(void)shell;
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != ' ' && line[*i] != '$')
		(*i)++;
	end = *i;
	env = ft_substr(line, start, end - start);
	if (!env)
		exit(1);
	value = getenv(env);
	if (!value)
		value = "";
	free(env);
	return (value);
}

static int	expand_env(t_shell *shell, char **line, int i)
{
	int		start;
	int		end;
	char	*value;
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
		value = fetch_env(shell, *line, &i);
	printf("value: %s\n", value);
	new = join_n_free(ft_substr(*line, 0, start), ft_strdup(value));
	if (!new)
		exit(1);
	*line = join_n_free(new, ft_strdup(&(*line)[i]));
	printf("line: %s\n", *line);
	if (!*line)
		exit(1);
	return (start + ft_strlen(value) - 1);
}

void	check_expands(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		inside_doubles;

	i = 0;
	inside_doubles = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\"')
			inside_doubles = !inside_doubles;
		if (cmd->line[i + 1] && cmd->line[i] == '\'' && !inside_doubles)
			i = skip_quotes(cmd->line, i);
		if (cmd->line[i + 1] && cmd->line[i] == '$')
			i = expand_env(shell, &cmd->line, i);
		if (cmd->line[i] == '*')
		{
			// handle wildcard
		}
		i++;
	}
}
