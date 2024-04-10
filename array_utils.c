/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:07:09 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/10 11:26:08 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**copy_array(t_shell *shell, char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	new_array = malloc(sizeof(char *) * (array_len(array) + 1));
	if (!new_array)
		error(shell, MALLOC, FATAL, 1);
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			free_array(&new_array);
			error(shell, MALLOC, FATAL, 1);
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

int	find_in_array(char **array, char *identifier)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], identifier, ft_strlen(identifier)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	remove_from_array(char **array, char *identifier)
{
	int	i;

	i = 0;
	if (!find_in_array(array, identifier))
		return ;
	while (array[i])
	{
		if (ft_strncmp(array[i], identifier, ft_strlen(identifier)) == 0)
		{
			free(array[i]);
			array[i] = NULL;
			break ;
		}
		i++;
	}
	while (array[i + 1])
	{
		array[i] = array[i + 1];
		i++;
	}
	array[i] = NULL;
}

char	**add_to_array(t_shell *shell, char **array, char *new, t_status mode)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = malloc(sizeof(char *) * (array_len(array) + 2));
	if (!new_array)
		malloc_error(shell, new, mode);
	while (array[++i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			free_array(&new_array);
			malloc_error(shell, new, mode);
		}
	}
	new_array[i] = ft_strdup(new);
	if (!new_array[i])
	{
		free_array(&new_array);
		malloc_error(shell, new, mode);
	}
	new_array[i + 1] = NULL;
	free_array(&array);
	return (new_array);
}
