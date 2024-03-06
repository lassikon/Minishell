/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:19:45 by okarejok          #+#    #+#             */
/*   Updated: 2024/03/05 16:06:07 by lkonttin         ###   ########.fr       */
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
