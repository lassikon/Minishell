/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:16:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/01 16:12:05 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_cmd **cmd_tree)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_tree[i])
	{
		j = 0;
		ft_putstr_fd("cmd: ", 1);
		ft_putendl_fd(cmd_tree[i]->cmd, 1);
		ft_putstr_fd("args: ", 1);
		while (cmd_tree[i]->args[j])
		{
			ft_putstr_fd(cmd_tree[i]->args[j], 1);
			ft_putstr_fd(" ", 1);
			j++;
		}
		ft_putstr_fd("\nredirs: ", 1);
		j = 0;
		while (cmd_tree[i]->redir[j])
		{
			ft_putstr_fd(cmd_tree[i]->redir[j], 1);
			ft_putstr_fd(" ", 1);
			j++;
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
