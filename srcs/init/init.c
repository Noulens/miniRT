/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/15 19:22:56 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	rt_name_checker(char *path)
{
	int	i;
	int	fd;
	int	map;

	map = 1;
	if (path == NULL)
		map = 0;
	i = ft_strlen(path);
	if (i <= 3)
		map = 0;
	if (!ft_strnstr(path + i - 3, ".rt", 3))
		map = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		map = 0;
	else
		close(fd);
	if (!map)
		ft_fprintf(2, RED"Usage : ./miniRT <filename.rt>\n"RESET);
	return (map);
}
