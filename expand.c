/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:11:41 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/09 16:36:34 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_character(char c)
{
	if (c == '\0' || c == ' ' || c == '/' || c == '$'
		|| c == '\"' || c == '\'' || c == '=' || c == ':'
		|| c == '@')
		return (1);
	return (0);
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

static char	*get_expand(t_shell *shell, char *line)
{
	int		len;
	char	*env;
	char	*value;

	len = 0;
	if (line[len] == '?')
		return (get_exit_status(shell));
	while (!end_character(line[len]))
		len++;
	if (len == 0)
		return (dup_empty_str(shell));
	env = ft_substr(line, 0, len);
	if (!env)
		error(shell, MALLOC, FATAL, 1);
	value = ft_getenv(shell, env);
	if (!value)
		value = dup_empty_str(shell);
	free(env);
	return (value);
}

static void	expand_env(t_shell *shell, char **line, int *i)
{
	int		start;
	char	*value;
	char	*new;

	(*i)++;
	start = *i;
	if (end_character((*line)[start]) && (*line)[start + 1] == '\0')
		return ;
	value = get_expand(shell, &(*line)[start]);
	(*i) = start + ft_strlen(value) - 1;
	new = join_n_free(ft_substr(*line, 0, start - 1), value);
	if (!new)
		error(shell, MALLOC, FATAL, 1);
	if ((*line)[start] != '?')
		while (!end_character((*line)[start]))
			start++;
	else
		start++;
	if ((*line)[start])
		new = join_n_free(new, ft_strdup(&(*line)[start]));
	if (!new)
		error(shell, MALLOC, FATAL, 1);
	free(*line);
	*line = new;
}

void	expand(t_shell *shell, char **line)
{
	int		i;
	int		inside_doubles;

	if (shell->status == ERROR)
		return ;
	i = 0;
	inside_doubles = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"')
			inside_doubles = !inside_doubles;
		if ((*line)[i + 1] && (*line)[i] == '\'' && !inside_doubles)
			i = skip_quotes(*line, i);
		if ((*line)[i + 1] && (*line)[i] == '$' && (*line)[i + 1] != ' ')
		{
			expand_env(shell, line, &i);
			continue ;
		}
		i++;
	}
}
