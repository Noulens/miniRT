/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:58:53 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/22 22:35:39 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rt_name_checker(char *path)
{
	size_t	i;
	int		map;

	map = 1;
	if (path == NULL)
		map = 0;
	i = ft_strlen(path);
	if (i <= 3)
		map = 0;
	if (!ft_strnstr(path + i - 3, ".rt", 3))
		map = 0;
	if (!map)
		ft_fprintf(2, RED"Error\nUsage : ./miniRT <filename.rt>\n"RESET);
	return (map);
}

static int	get_space_attribute(char *line, t_scene *scn, char chr)
{
	static int	nba;
	static int	nbc;
	static int	nbl;

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
	else if (chr == 'X')
	{
		if (nba != 1 || nbl != 1 || nbc != 1)
			return (ft_fprintf(2, RED "Error\ndata missing or in excess\n" RESET), 1);
	}
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
	{
		++line;
	}
	if (*line == '\0' || *line == '\n')
		return (0);
	else if (!ft_strncmp(line, "A", 1) || !ft_strncmp(line, "C", 1)
		|| !ft_strncmp(line, "L", 1))
	{
		return(get_space_attribute(line, scn, *line));
	}
	else if (!ft_strncmp(line, "pl", 2) || !ft_strncmp(line, "cy", 2)
		|| !ft_strncmp(line, "sp", 2))
	{
		return(get_obj_attribute(line, scn));
	}
	else
		return (ft_fprintf(2, RED"Error\nunknown element in .rt file\n"RESET), 1);
}

int	parse(t_scene *scn, char *str)
{
	int		fd;
	char	*line;
	int		ok;

	ok = FAIL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "Error\nCould not open .rt file\n"), 1);
	line = get_next_line(fd);
	while (line)
	{
		ok = get_infos(line, scn);
		if (ok != 0)
			return(free(line), ok);
		free(line);
		line = get_next_line(fd);
	}
	if (get_space_attribute(NULL, NULL, 'X') == 1)
		return (ft_fprintf(2, RED"Error\nACL format not respected\n"RESET), 1);
	return (ok);
}
