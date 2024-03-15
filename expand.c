/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:11:41 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/15 16:14:34 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fetch_env(t_shell *shell, char *line, int *i)
{
	int		start;
	int		end;
	char	*env;
	char	*value;

	// printf("fetch_env from line: %s\n", line);
	start = *i;
	if (line[*i] == '\"')
		return ("$");
	(*i)++;
	while (line[*i] && line[*i] != ' ' && line[*i] != '$' && line[*i] != '\"')
		(*i)++;
	end = *i;
	env = ft_substr(line, start, end - start);
	if (!env)
		error(shell, MALLOC, FATAL, 1);
	value = getenv(env);
	if (!value)
		value = "";
	free(env);
	return (value);
}

static int	expand_env(t_shell *shell, char **line, int i)
{
	int		start;
	char	*value;
	char	*new;

	start = i;
	i++;
	if ((*line)[i] == '?')
	{
		value = ft_itoa(WEXITSTATUS(shell->exit_status));
		i++;
	}
	else
		value = fetch_env(shell, *line, &i);
	new = join_n_free(ft_substr(*line, 0, start), ft_strdup(value));
	if (!new)
		error(shell, MALLOC, FATAL, 1);
	*line = join_n_free(new, ft_strdup(&(*line)[i]));
	if (!*line)
		error(shell, MALLOC, FATAL, 1);
	return (start + ft_strlen(value) - 1);
}

void	check_expands(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		inside_doubles;

	if (shell->status == ERROR)
		return ;
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
		i++;
	}
}
