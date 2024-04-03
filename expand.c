/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:11:41 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/03 12:38:31 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_character(char c)
{
	if (c == '\0' || c == ' ' || c == '/' || c == '$'
		|| c == '\"' || c == '\'' || c == '=' || c == ':')
		return (1);
	return (0);
}

static char	*get_expand(t_shell *shell, char *line, int *i)
{
	int		start;
	char	*env;
	char	*value;

	start = *i;
	while (!end_character(line[*i]))
		(*i)++;
	if (*i == start)
		return (dup_empty_str(shell));
	env = ft_substr(line, start, *i - start);
	if (!env)
		error(shell, MALLOC, FATAL, 1);
	value = ft_getenv(shell, env);
	if (!value)
		value = dup_empty_str(shell);
	if (!value)
		value = ft_strdup(" ");
	free(env);
	return (value);
}

static char	*get_exit_status(t_shell *shell)
{
	char	*value;

	if (shell->exit_status > 255)
		value = ft_itoa(WEXITSTATUS(shell->exit_status));
	else
		value = ft_itoa(shell->exit_status);
	if (!value)
		error(shell, MALLOC, FATAL, 1);
	return (value);
}

static int	expand_env(t_shell *shell, char **line, int i)
{
	int		start;
	char	*value;
	char	*new;

	start = i;
	i++;
	if (end_character((*line)[i]) && (*line)[i + 1] == '\0')
		return (i);
	if ((*line)[i] == '?')
	{
		value = get_exit_status(shell);
		i++;
	}
	else
		value = get_expand(shell, *line, &i);
	new = join_n_free(ft_substr(*line, 0, start), value);
	if (!new)
		error(shell, MALLOC, FATAL, 1);
	new = join_n_free(new, ft_strdup(&(*line)[i]));
	if (!new)
		error(shell, MALLOC, FATAL, 1);
	free(*line);
	*line = new;
	return (start + ft_strlen(value));
}

int	expand(t_shell *shell, char **line)
{
	int		i;
	int		inside_doubles;
	int		expands;

	if (shell->status == ERROR)
		return (0);
	i = 0;
	inside_doubles = 0;
	expands = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"')
			inside_doubles = !inside_doubles;
		if ((*line)[i + 1] && (*line)[i] == '\'' && !inside_doubles)
			i = skip_quotes(*line, i);
		if ((*line)[i + 1] && (*line)[i] == '$' && (*line)[i + 1] != ' ')
		{
			expands++;
			i = expand_env(shell, line, i);
			continue ;
		}
		i++;
	}
	return (expands);
}
