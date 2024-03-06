/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:45 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/06 14:57:12 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	paths(t_shell *shell, char **envp)
{
	char	**paths;

	if (envp != NULL)
	{
		while (*envp)
		{
			if (!ft_strncmp(*envp, "PATH", 4))
			{
				paths = ft_split(*envp + 5, ':');
				if (paths == NULL)
                    printf("paths is null");
					//handle_perror(p, ERROR_MALLOC, 1, 1);
				shell->paths = paths;
				return ;
			}
			envp++;
		}
	}
}

char	*find_home_dir(t_shell *shell)
{
	char	*home;

	home = NULL;
	if (shell->env != NULL)
	{
		while (*shell->env)
		{
			if (!ft_strncmp(*shell->env, "HOME", 4))
			{
				home = *shell->env + 5;
				if (home == NULL)
                    printf("home not found :(");
				return (home);
			}
			shell->env++;
		}
	}
	return (home);
}
