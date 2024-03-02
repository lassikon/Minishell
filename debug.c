/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:16:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/02 16:31:22 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	printf("\n");
	while (i < shell->cmd_count)
	{
		j = 0;
		printf("cmd[%d]: %s\n", i, shell->cmd_tree[i].cmd);
		while (shell->cmd_tree[i].args[j])
		{
			printf("args[%d]: %s\n", j, shell->cmd_tree[i].args[j]);
			j++;
		}
		j = 0;
		printf("redir_count: %d\n", shell->cmd_tree[i].redir_count);
		while (j < shell->cmd_tree[i].redir_count)
		{
			printf("redir[%d]: %s\n", j, shell->cmd_tree[i].redir[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
