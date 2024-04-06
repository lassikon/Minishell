/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:16:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/06 19:24:38 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	printf("\n");
	write(1, "Printing tree\n", 14);
	printf("cmd_count: %d\n", shell->cmd_count);
	while (i < shell->cmd_count)
	{
		j = 0;
		printf("cmd[%d]: %s\n", i, shell->cmd_tree[i].cmd);
		printf("arg_count: %d\n", shell->cmd_tree[i].arg_count);
		if (shell->cmd_tree[i].arg_count > 0)
		{
			while (shell->cmd_tree[i].args[j])
			{
				printf("args[%d]: %s\n", j, shell->cmd_tree[i].args[j]);
				j++;
			}
			printf("args[%d]: %s\n", j, shell->cmd_tree[i].args[j]);
		}
		j = 0;
		printf("redir_count: %d\n", shell->cmd_tree[i].redir_count);
		while (j < shell->cmd_tree[i].redir_count)
		{
			printf("redir[%d]: %s\n", j, shell->cmd_tree[i].redir[j]);
			j++;
		}
		printf("\n");
		printf("exit_status: %d\n\n", shell->exit_status);
		i++;
	}
}

void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}
