/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:46:25 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/06 14:12:15 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	exit(0);
}

void	export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		printf("Export without arguments\n");
		env(shell);
		exit(0);
	}
	printf("Exporting %s\n", cmd->args[1]);
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			if (check_unclosed_quotes(cmd->args[i]))
			{
				printf("Unclosed quotes in %s\n", cmd->args[i]);
				return ;
			}
			shell->env = add_to_array(shell->env, cmd->args[i]);
		}
		i++;
	}
	printf("New env:\n");
	print_env(shell);
}

void	unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;
	char	**new_env;

	i = 0;
	k = 0;
	if (!cmd->args[1])
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	printf("Unsetting %s\n", cmd->args[1]);
	new_env = malloc(sizeof(char *) * (array_len(shell->env) + 1));
	if (!new_env)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	while (shell->env[i])
	{
		j = 1;
		while (cmd->args[j])
		{
			if (!ft_strncmp(shell->env[i], cmd->args[j], ft_strlen(cmd->args[j])))
			{
				i++;
				j = 1;
			}
			else
				j++;
		}
		new_env[k] = ft_strdup(shell->env[i]);
		i++;
		k++;
	}
	new_env[k] = NULL;
	free_array(shell->env);
	shell->env = new_env;
	printf("New env:\n");
	print_env(shell);
}
void	child_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && !cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		env(shell);
	else
		return ;
}

int	parent_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "export", 7) == 0 && cmd->args[1])
		export(shell, cmd);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		unset(shell, cmd);
	else
		return (0);
	return (1);
}
