/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:49:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/06 18:17:17 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_shell *shell, char *msg, t_error status, int code)
{
	if (status == FATAL)
	{
		printf("Fatal error: %s\n", msg);
		free_tree(shell);
		free_array(shell->env);
		exit(code);
	}
}
