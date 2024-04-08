/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:45 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/08 18:51:06 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_increment(t_shell *shell)
{
	int		shlvl;
	char	*shlvl_str;
	char	*shlvl_prompt;

	shlvl_str = ft_getenv(shell, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
		shlvl = shlvl + 1;
		free(shlvl_str);
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		error(shell, MALLOC, FATAL, 1);
	remove_from_array(shell->env, "SHLVL=");
	shlvl_prompt = ft_strjoin("SHLVL=", shlvl_str);
	if (!shlvl_prompt)
		error(shell, MALLOC, FATAL, 1);
	shell->env = add_to_array(shell, shell->env, shlvl_prompt);
	free(shlvl_str);
	free(shlvl_prompt);
}

void	paths(t_shell *shell, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			shell->paths = ft_split(envp[i] + 5, ':');
			if (shell->paths == NULL)
				error(shell, MALLOC, FATAL, 1);
			return ;
		}
		i++;
	}
}

char	*ft_getenv(t_shell *shell, char *to_find)
{
	char	*aux;
	int		i;
	int		len;

	i = 0;
	if (!to_find)
		return (NULL);
	len = ft_strlen(to_find);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], to_find, len))
		{
			if (shell->env[i][len] == '=')
			{
				aux = ft_strdup(shell->env[i] + len + 1);
				if (aux == NULL)
					error(shell, MALLOC, FATAL, 1);
				return (aux);
			}
		}
		i++;
	}
	return (NULL);
}
