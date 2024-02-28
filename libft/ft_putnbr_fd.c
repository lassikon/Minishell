/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:14:08 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/06 15:31:53 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbl;

	nbl = n;
	if (nbl < 0)
	{
		ft_putchar_fd('-', fd);
		nbl = -nbl;
	}
	if (nbl >= 10)
	{
		ft_putnbr_fd(nbl / 10, fd);
		nbl = nbl % 10;
	}
	ft_putchar_fd(nbl + '0', fd);
}
