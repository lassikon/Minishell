/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:45 by okarejok          #+#    #+#             */
/*   Updated: 2024/04/10 11:52:30 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shlvl_warning(int shlvl)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(shlvl, 2);
	ft_putendl_fd(") too high, resetting to 1", 2);
}

static void	export_shlvl(t_shell *shell, char **shlvl_str)
{
	char	*output;

	remove_from_array(shell->env, "SHLVL=");
	output = ft_strjoin("SHLVL=", *shlvl_str);
	if (!output)
	{
		free(*shlvl_str);
		*shlvl_str = NULL;
		error(shell, MALLOC, FATAL, 1);
	}
	shell->env = add_to_array(shell, shell->env, output, FREEABLE);
	free(*shlvl_str);
	free(output);
}

void	shlvl_increment(t_shell *shell)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl_str = ft_getenv(shell, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
		else
			shlvl = shlvl + 1;
		if (shlvl > 1000)
		{
			shlvl_warning(shlvl);
			shlvl = 1;
		}
		free(shlvl_str);
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		error(shell, MALLOC, FATAL, 1);
	export_shlvl(shell, &shlvl_str);
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
