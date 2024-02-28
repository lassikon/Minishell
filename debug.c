/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:16:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/28 16:27:54 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_shell *shell)
{
	int i;
	int j;

	i = 0;
	printf("\n");
	while (shell->cmd_tree[i])
	{
		j = 0;
		while (shell->cmd_tree[i][j])
		{
			printf("cmd_tree[%d][%d]: %s\n", i, j, shell->cmd_tree[i][j]);
			j++;
		}
		if (shell->cmd_tree[i + 1])
			printf("PIPE\n");
		i++;
	}
	printf("\n");
}
