/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:07:09 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/06 11:29:31 by lkonttin         ###   ########.fr       */
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

int	copy_array(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			free_array(dst);
			return (-1);
		}
		i++;
	}
	return (i);
}

char	**add_to_array(char **array, char *new)
{
	int		i;
	char	**new_array;

	i = array_len(array);
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = copy_array(array, new_array);
	if (i == -1)
		return (NULL);
	new_array[i] = ft_strdup(new);
	if (!new_array[i])
	{
		free_array(new_array);
		return (NULL);
	}
	new_array[i + 1] = NULL;
	free_array(array);
	return (new_array);
}