/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:57 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 11:10:18 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	s;

	d = 0;
	s = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[d] && d < dstsize)
		d++;
	while ((d + s + 1) < dstsize && src[s] != '\0')
	{
		dst[d + s] = src[s];
		s++;
	}
	if (d < dstsize)
		dst[d + s] = '\0';
	return (d + ft_strlen(src));
}
/* d is incremented to the end of dst or to dstsize, whichever is smaller,
while s is the index in src.
Appends at most dstsize - (d + s + 1) characters from src to dst.
NUL-terminates if d (original length of dst) is smaller than dstsize.
Returns d + ft+strlen(src); if retval >= dstsize, truncation occurred.
*/