/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:41:04 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/10 11:51:46 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_to_heredoc(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	heredoc(t_shell *shell, t_cmd *cmd_vars)
{
	int		fd;
	int		i;

	(void)shell;
	if (cmd_vars->redir_count == 0)
		return ;
	i = 0;
	while (cmd_vars->redir[i])
	{
		if (ft_strncmp(cmd_vars->redir[i], "<<", 2) == 0)
		{
			fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
			{
				printf("Error opening the file! %s\n", "/tmp/heredoc");
				exit(1);
			}
			write_to_heredoc(cmd_vars->redir[i] + 2, fd);
			close(fd);
			cmd_vars->redir[i] = ft_strdup("< /tmp/heredoc");
			if (!cmd_vars->redir[i])
				exit(1);
		}
		i++;
	}
}
