/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:07:06 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 10:44:15 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*str_src;
	size_t	i;

	str_src = (char *)src;
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < (dstsize - 1) && str_src[i] != '\0')
	{
		dst[i] = str_src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/* Copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.

Returns the total length of the string it tried to create.*/