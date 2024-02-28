/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:50:52 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 13:50:28 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	check_max;

	check_max = count * size;
	if (size != 0 && count != check_max / size)
		return (NULL);
	if (count != 0 && size != check_max / count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == (NULL))
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}
// Checks for (count * size) being over size_t max