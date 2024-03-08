/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:41:04 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/08 14:33:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	write_to_heredoc(t_cmd *cmd_vars, int i, int fd)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, cmd_vars->redir[i] + 3))
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
}

void	heredoc(t_shell *shell, t_cmd *cmd_vars)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		i;
	int		last;

	i = 0;
	while (cmd_vars->redir[i])
	{
		if (cmd_vars->redir[i][0] == '<' && cmd_vars->redir[i][1] == '<')
		{
			fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
			write_to_heredoc(cmd_vars, i, fd);
			close(fd);
			cmd_vars->heredoc_count++;
			cmd_vars->redir[i] = ft_strdup("/tmp/heredoc");
			last = i;
		}
		i++;
	}
	
} */
