/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:41:04 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/06 18:21:19 by lkonttin         ###   ########.fr       */
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
			expand(shell, &line);
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
	free_array(&shell->env);
	close(shell->history_fd);
	exit(0);
}

int	add_heredoc_to_array(t_shell *shell, char **redir, char **file)
{
	if (WTERMSIG(shell->exit_status) == SIGINT)
	{
		shell->status = ERROR;
		shell->exit_status = 1;
		free(*file);
		return (1);
	}
	free(*redir);
	*redir = ft_strjoin("< ", *file);
	free(*file);
	if (!*redir)
		error(shell, MALLOC, FATAL, 1);
	return (0);
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
			waitpid(pid, &shell->exit_status, 0);
			if (add_heredoc_to_array(shell, &cmd->redir[i], &file))
				return ;
			shell->heredoc_index++;
		}
		i++;
	}
}
