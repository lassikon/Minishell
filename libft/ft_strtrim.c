/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:22:15 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 12:20:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	str_len;
	size_t	start;
	size_t	end;
	size_t	trimmed_len;

	str_len = ft_strlen(s1);
	start = 0;
	if (!set || str_len == 0)
		return (ft_strdup(s1));
	while (start < str_len)
	{
		if (ft_strchr(set, s1[start]) == NULL)
			break ;
		start++;
	}
	end = str_len - 1;
	while (end > 0 && end > start)
	{
		if (ft_strchr(set, s1[end]) == NULL)
			break ;
		end--;
	}
	trimmed_len = str_len - start - (str_len - end) + 1;
	return (ft_substr(s1, start, trimmed_len));
}
/*
If s1 or set are blank, uses ft_strdup to malloc for an empty string.
Otherwise iterates through s1 from both ends until s1[] not found in set,
then saves start and end locations of the first non-set characters found.

Uses ft_substr to produce the trimmed string from s1 using start 
and trimmed_len.
trimmed_len = str_len minus the trimming from both ends, and +1 because end was
set to (str_len - 1) in order to to not start iterating from null terminator.
*/
