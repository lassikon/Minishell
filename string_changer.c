/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_changer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:09:26 by lkonttin          #+#    #+#             */
/*   Updated: 2024/03/05 14:14:15 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	modify_string(char **line)
{
	printf("Modifying line: %s\n", *line);
	*line = "Modified!";
}

int	main(void)
{
	char	*line;

	line = malloc(100);
	line = "Hello, world!";
	printf("Original line: %s\n", line);
	modify_string(&line);
	printf("Modified line: %s\n", line);
	return (0);
}