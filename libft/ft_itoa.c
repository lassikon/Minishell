/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:39 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 15:09:25 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_count(long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
		n = -n;
	while (n / 10 >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbl;
	char	*str;
	size_t	len;

	nbl = n;
	len = digit_count(nbl);
	if (nbl < 0)
	{
		nbl = -nbl;
		len++;
	}
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbl % 10 + 48;
		nbl = nbl / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
