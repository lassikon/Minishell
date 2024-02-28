/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:38:10 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 10:32:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	unsigned char	*mem_dst;
	unsigned char	*mem_src;
	size_t			i;

	mem_dst = (unsigned char *)dst;
	mem_src = (unsigned char *)src;
	if (dst == (NULL) && src == (NULL))
		return (dst);
	i = 0;
	while (i < n)
	{
		mem_dst[i] = mem_src[i];
		i++;
	}
	return (dst);
}
/* Copies n bytes from memory area src to memory area
dst.  If dst and src overlap, behavior is undefined. */