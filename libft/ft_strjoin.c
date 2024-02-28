/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:03:43 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 12:13:34 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	d;
	size_t	s;
	char	*str;

	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	d = 0;
	while (s1[d])
	{
		str[d] = s1[d];
		d++;
	}
	s = 0;
	while (s2[s])
	{
		str[d + s] = s2[s];
		s++;
	}
	str[d + s] = '\0';
	return (str);
}
/*
Allocates (with malloc) and returns a new string, which
is the result of the concatenation of ’s1’ and ’s2’.
*/