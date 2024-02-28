/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:53:21 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 10:23:00 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 040 && c <= 0176)
		return (1);
	else
		return (0);
}
/* Tests for a printable character, which is any 
character between octal 040 and 0176 inclusive. */