/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:38:34 by lkonttin          #+#    #+#             */
/*   Updated: 2023/11/07 13:56:26 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	max_check(long nbr, long temp, int sign)
{
	if (nbr < temp)
	{
		if (sign > 0)
			return (-1);
		return (0);
	}
	return (1);
}
// Returns -1 if nbr goes over max long and was positive, or 0 if negative

int	ft_atoi(const char *str)
{
	int		sign;
	long	nbr;
	long	previous;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	if (*str < '0' && *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		previous = nbr;
		nbr = nbr * 10 + *str - '0';
		if (max_check(nbr, previous, sign) != 1)
			return (max_check(nbr, previous, sign));
		str++;
	}
	return ((int)nbr * sign);
}
