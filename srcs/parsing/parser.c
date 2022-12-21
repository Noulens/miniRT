/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:58:53 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 16:20:12 by waxxy            ###   ########.fr       */
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

static int	get_space_attribute(char *line, t_scene *scn)
{

	return(0);
}

static int	get_obj_attribute(char *line, t_scene *scn)
{

	return(0);
}

static int	get_infos(char *line, t_scene *scn)
{
	(void)scn;
	while(*line == ' ')
		++line;
	if (ft_cmpchr(line, "A", ' '))
		;//get A
	else if (ft_cmpchr(line, "C", ' '))
		; //get C
	else if (ft_cmpchr(line, "L", ' '))
		; // get L
	else if (ft_cmpchr(line, "pl", ' '))
		; // get object pl
	else if (ft_cmpchr(line, "cy", ' '))
		; // get object cy
	else if (ft_cmpchr(line, "sp", ' '))
		; // get object sp
	else
		return(ft_fprintf(2, RED"unknown element in .rt file\n"RESET), 1);
}

int	parse(t_scene *scn, char *str)
{
	int		fd;
	char	*line;
	int		ok;

	ok = EXIT_FAILURE;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "Could not open .rt file\n"), 1);
	line = get_next_line(fd);
	while(line)
	{
		ok = get_infos(line, scn);
		free(line);
		line = get_next_line(fd);
	}
	return (ok);
}
