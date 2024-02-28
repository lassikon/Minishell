/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:39:34 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 10:39:16 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*mem_dst;
	unsigned char	*mem_src;

	if (dst == (NULL) && src == (NULL))
		return (dst);
	mem_dst = (unsigned char *)dst;
	mem_src = (unsigned char *)src;
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len > 0)
		{
			mem_dst[len - 1] = mem_src[len - 1];
			len--;
		}
	}
	return (dst);
}
/* Copies len bytes from string src to string dst.
If dst > src, copies backwards to stop overlap
from causing problems. */