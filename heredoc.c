/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:41:04 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/07 15:28:35 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_heredocs(char **redir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (redir[i])
	{
		if (ft_strncmp(redir[i], "<<", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

static void	init_heredoc(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd->heredoc = (char ***)malloc(sizeof(char **) * cmd->heredoc_count);
}

void	heredoc(t_shell *shell, t_cmd *cmd)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	cmd->heredoc_count = count_heredocs(cmd->redir);
	if (cmd->heredoc_count == 0)
		return ;
	init_heredoc(shell, cmd);
	line = ft_strdup("");
	tmp = readline("heredoc> ");
	while (ft_strncmp(tmp, cmd->redir[i][0] + 2, 2) != 0)
	{
		line = ft_strjoin(line, tmp);
		tmp = readline("heredoc> ");
	}
}
