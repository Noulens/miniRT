/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:58:53 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/23 17:22:39 by tnoulens         ###   ########.fr       */
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
		ft_fprintf(2, "Error\nin filename\n");
	return (map);
}

static int	check_numbers_of_type(int nba, int nbc, int nbl)
{
	if (BONUS == 0)
	{
		if (nba != 1 || nbl != 1 || nbc != 1)
			return (ft_fprintf(2, "Error\nACL not unique\n"), 1);
	}
	else
	{
		if (nba != 1 || nbl < 1 || nbc != 1)
			return (ft_fprintf(2, "Error\nACL not good\n"), 1);
	}
	return (SUCCESS);
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
	else if (chr == 0 && check_numbers_of_type(nba, nbc, nbl))
	{
		return (FAIL);
	}
	return (SUCCESS);
}

static int	get_infos(char *line, t_scene *scn)
{
	while (*line == ' ')
		++line;
	if (*line == '\0' || *line == '\n')
		return (0);
	else if (!ft_strncmp(line, "A", 1) || !ft_strncmp(line, "C", 1)
		|| !ft_strncmp(line, "L", 1))
		return (get_space_attribute(line, scn, *line));
	else if (!ft_strncmp(line, "pl", 2))
		return (line += 2, parse_pl(line, scn));
	else if (!ft_strncmp(line, "cy", 2))
		return (line += 2, parse_cy(line, scn));
	else if (!ft_strncmp(line, "sp", 2))
		return (line += 2, parse_sp(line, scn));
	else if (BONUS == TRUE)
	{
		if (!ft_strncmp(line, "co", 2))
			return (line += 2, parse_co(line, scn));
		else
			return (ft_fprintf(2, "Error\nunknown element in .rt\n"), FAIL);
	}
	else
		return (ft_fprintf(2, "Error\nunknown element in .rt\n"), FAIL);
}

int	parse(t_scene *scn, char *str)
{
	int		fd;
	char	*line;
	int		ok;

	ok = FAIL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "Error\nCould not open .rt file\n"), FAIL);
	line = get_next_line(fd);
	while (line)
	{
		ok = get_infos(line, scn);
		if (ok != 0)
			return (close(fd), free(line), ok);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (get_space_attribute(NULL, NULL, 0) == FAIL)
		return (ft_fprintf(2, "Error\nACL format not respected\n"), FAIL);
	scn->num_objects_in_scene = objlstsize(scn->objects);
	scn->num_lamps = objlstsize_l(scn->lamp);
	if (list_to_tab_l(scn) || list_to_tab(scn))
		return (FAIL);
	return (SUCCESS);
}
