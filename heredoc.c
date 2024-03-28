/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:41:04 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/28 15:48:44 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_filename(t_shell *shell)
{
	char	*file;
	char	*tmp;

	tmp = ft_itoa(shell->heredoc_index);
	if (!tmp)
		error(shell, MALLOC, FATAL, 1);
	file = ft_strjoin("/tmp/heredoc", tmp);
	free(tmp);
	if (!file)
		error(shell, MALLOC, FATAL, 1);
	return (file);
}

static void	write_to_heredoc(t_shell *shell, char *limiter, int fd)
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
		if (ft_strchr(line, '$'))
			check_expands(shell, &line);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	heredoc_child(t_shell *shell, t_cmd *cmd, char *file, int i)
{
	int		fd;

	toggle_signal(HEREDOC);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		p_error(shell, file, FATAL, 1);
	write_to_heredoc(shell, cmd->redir[i] + 2, fd);
	close(fd);
	free_all(shell);
	free_array(shell->env);
	close(shell->history_fd);
	toggle_signal(DEFAULT);
	exit(0);
}

void	heredoc(t_shell *shell, t_cmd *cmd)
{
	int		pid;
	int		i;
	char	*file;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (ft_strncmp(cmd->redir[i], "<<", 2) == 0)
		{
			file = heredoc_filename(shell);
			pid = fork();
			if (pid == -1)
				p_error(shell, "fork", FATAL, 1);
			if (pid == 0)
				heredoc_child(shell, cmd, file, i);
			else
				waitpid(pid, &shell->exit_status, 0);
			if (WTERMSIG(shell->exit_status) != SIGINT)
			{
				free(cmd->redir[i]);
				cmd->redir[i] = ft_strjoin("< ", file);
				if (!cmd->redir[i])
					error(shell, MALLOC, FATAL, 1);
			}
			else
				shell->status = ERROR;
			free(file);
			shell->heredoc_index++;
		}
		i++;
	}
}
