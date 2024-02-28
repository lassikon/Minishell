/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:25 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 12:32:20 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	if (haystack == (NULL) && len == 0)
		return (NULL);
	if (needle[0] == '\0' || needle == haystack)
		return ((char *)haystack);
	h = 0;
	while (haystack[h] != '\0' && h < len)
	{
		n = 0;
		while (haystack[h + n] == needle[n] && (h + n < len))
		{
			n++;
			if (needle[n] == '\0')
			{
				return ((char *)haystack + h);
			}
		}
		h++;
	}
	return (NULL);
}
/*
Locates the first occurrence of the null-terminated string needle in
the string haystack, where not more than len characters are searched.

If needle is an empty string, haystack is returned; if needle occurs
nowhere in haystack, NULL is returned; otherwise a pointer to the first
character of the first occurrence of needle is returned.
*/