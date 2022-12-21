/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:58:53 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 20:13:38 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rt_name_checker(char *path)
{
	int	i;
	int	map;

	map = 1;
	if (path == NULL)
		map = 0;
	i = ft_strlen(path);
	if (i <= 3)
		map = 0;
	if (!ft_strnstr(path + i - 3, ".rt", 3))
		map = 0;
	if (!map)
		ft_fprintf(2, RED"Usage : ./miniRT <filename.rt>\n"RESET);
	return (map);
}

static int	get_space_attribute(char *line, t_scene *scn, char chr)
{
	static int	nba;
	static int	nbc;
	static int	nbl;

	if (nba > 1 || nbc > 1 || nbl > 1)
		return (FAIL);
	if (chr == 'A')
	{
		++nba;
		return (get_infos_a(++line, scn));
	}
	else if (chr == 'C')
	{
		++nbc;
		return (get_infos_c(++line, scn));
	}
	else if (chr == 'L')
	{
		++nbl;
		return (get_infos_l(++line, scn));
	}
	else
		if (nba + nbl + nbc != 3)
			return (ft_fprintf(2, RED "element missing\n" RESET), 1);
	return(SUCCESS);
}

static int	get_obj_attribute(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (0);
}

static int	get_infos(char *line, t_scene *scn)
{
	while (*line == ' ')
		++line;
	if (ft_cmpchr(line, "A", ' ') || ft_cmpchr(line, "C", ' ')
		|| ft_cmpchr(line, "L", ' '))
		return(get_space_attribute(line, scn, *line));
	else if (ft_cmpchr(line, "pl", ' ') || ft_cmpchr(line, "cy", ' ')
		|| ft_cmpchr(line, "sp", ' '))
		return(get_obj_attribute(line, scn));
	else
		return (ft_fprintf(2, RED"unknown element in .rt file\n"RESET), 1);
}

int	parse(t_scene *scn, char *str)
{
	int		fd;
	char	*line;
	int		ok;

	ok = FAIL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "Could not open .rt file\n"), 1);
	line = get_next_line(fd);
	while (line)
	{
		ok = get_infos(line, scn);
		if (ok != 0)
			return(free(line), ok);
		free(line);
		line = get_next_line(fd);
	}
	return (ok);
}
