/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:07:09 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/09 12:01:50 by lkonttin         ###   ########.fr       */
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

/* int	copy_array(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			free_array(&dst);
			return (-1);
		}
		i++;
	}
	return (i);
} */

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

/* char	**remove_from_array(t_shell *shell, char **array, char *identifier)
{
	int		i;
	int		k;
	char	**new_array;

	i = 0;
	k = 0;
	new_array = malloc(sizeof(char *) * (array_len(array) + 1));
	if (!new_array)
		error(shell, MALLOC, FATAL, 1);
	while (array[i])
	{
		if (ft_strncmp(array[i], identifier, ft_strlen(identifier)) == 0)
		{
			free (array[i]);
			i++;
			continue ;
		}
		new_array[k] = array[i];
		free(array[i]);
		i++;
		k++;
	}
	new_array[k] = NULL;
	free(array);
	return (new_array);
} */

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

char	**add_to_array(t_shell *shell, char **array, char *new)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = malloc(sizeof(char *) * (array_len(array) + 2));
	if (!new_array)
		error(shell, MALLOC, FATAL, 1);
	while (array[++i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			free_array(&new_array);
			error(shell, MALLOC, FATAL, 1);
		}
	}
	new_array[i] = ft_strdup(new);
	if (!new_array[i])
	{
		free_array(&new_array);
		error(shell, MALLOC, FATAL, 1);
	}
	new_array[i + 1] = NULL;
	free_array(&array);
	return (new_array);
}

/* char	**add_to_array(t_shell *shell, char **array, char *new)
{
	int		i;
	char	**new_array;

	i = 0;
	new_array = malloc(sizeof(char *) * (array_len(array) + 2));
	if (!new_array)
		error(shell, MALLOC, FATAL, 1);
	while (array[i])
	{
		new_array[i] = array[i];
		free(array[i]);
		i++;
	}
	free(array);
	new_array[i] = ft_strdup(new);
	if (!new_array[i])
	{
		free_array(&new_array);
		error(shell, MALLOC, FATAL, 1);
	}
	new_array[i + 1] = NULL;
	return (new_array);
} */
