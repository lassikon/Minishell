/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:52:56 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 16:06:35 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees the memory allocated for every previous substring,
// then frees the array.
static void	free_array(char **str_array, size_t index)
{
	while (index > 0)
	{
		free(str_array[index -1]);
		index--;
	}
	free(str_array);
}

// Counts the number of substrings that need to be created
static size_t	substr_count(const char *s, char c)
{
	size_t	count;
	size_t	i;
	int		in_substr;

	count = 0;
	i = 0;
	in_substr = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			in_substr = 0;
		else if (in_substr == 0)
		{
			in_substr = 1;
			count++;
		}
		i++;
	}
	return (count);
}

// Returns the length of substring being created
static size_t	substr_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

// Chops s into substrings into str_array
static char	**array_creator(const char *s, char c, char **str_array)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0' && k < substr_count(s, c))
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			str_array[k] = ft_substr(s, i, substr_len(&s[i], c));
			if (!str_array[k])
			{
				free_array(str_array, k);
				return (NULL);
			}
			i = i + substr_len(&s[i], c);
		}
		k++;
	}
	str_array[k] = NULL;
	return (str_array);
}

char	**ft_split(const char *s, char c)
{
	char	**str_array;

	if (!s)
		return (NULL);
	str_array = (char **) malloc (sizeof(char *) * (substr_count(s, c) + 1));
	if (!str_array)
		return (NULL);
	if (!array_creator(s, c, str_array))
		return (NULL);
	return (str_array);
}
