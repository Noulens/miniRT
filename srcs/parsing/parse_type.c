/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:12:13 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/24 10:38:40 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_rgb(char *str)
{
	int	i;

	i = 0;
	while (*str == ' ')
		++str;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' || i > 3)
		return (ft_fprintf(2, "Error\nrgb not valid\n"), FAIL);
	++i;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' || i > 7)
		return (ft_fprintf(2, "Error\nrgb not valid\n"), FAIL);
	if (!ft_isdigit(str[++i]))
		return (ft_fprintf(2, "Error\nrgb not valid\n"), FAIL);
	while (ft_isdigit(str[i]))
		i++;
	if (i > 11)
		return (ft_fprintf(2, "Error\nrgb not valid\n"), FAIL);
	while (str[++i] != '\0')
		if (!ft_isspace(str[i]))
			return (ft_fprintf(2, "Error\nrgb not valid\n"), FAIL);
	return (rgb_range_checker(str));
}

int	atorgb(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (line[i] == ' ')
		++i;
	r = ft_atoi(line + i);
	while (line[i] != ',')
		++i;
	g = ft_atoi(line + ++i);
	while (line[i] != ',')
		++i;
	b = ft_atoi(line + ++i);
	return (ft_trgb(255, r, g, b));
}

int	get_infos_a(char *line, t_scene *scn)
{
	int	i;

	i = 0;
	if (count_element(line) != 2)
		return (ft_fprintf(2, "Error\nin A data: too much data\n"), FAIL);
	if (check_float_nb(&i, line))
		return (1);
	scn->alight.al = ft_atof(line);
	if (float_range_checker(scn->alight.al, 0.0f, 1.0f, TRUE) == FALSE)
		return (ft_fprintf(2, "Error\nin A data: value not in [0;1]\n"), FAIL);
	if (check_rgb(line + i) == SUCCESS)
	{
		scn->alight.color = atorgb(line + i);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

int get_infos_c(char *line, t_scene *scn)
{
	int	i;
	int j;
	int k;
	int	commas;

	if (count_element(line) != 3)
		return (ft_fprintf(2, "Error\nin C data, bad elements nb\n"), FAIL);
	if (check_fformat(&i, &commas, line))
		return (FAIL);
	get_floats(line, &scn->cam.pos, 'C');
	j = i;
	if (check_fformat(&i, &commas, line + j))
		return (1);
	if (get_floats(line + j, &scn->cam.orientation, 'c'))
		return (FAIL);
	k = i + j;
	i = k;
	while (*(line + k) == ' ')
		++line;
	if (check_float_nb(&k, line))
		return (FAIL);
	scn->cam.fov_w = ft_atof(line + i);
	if (!float_range_checker(scn->cam.fov_w, 0, 180, TRUE))
		return (ft_fprintf(2, "Error\nin C data: bad focal\n"), FAIL);
	return (SUCCESS);
}

int get_infos_l(char *line, t_scene *scn)
{
	int	i;
	int	j;
	int	commas;

	if (count_element(line) != 3)
		return (ft_fprintf(2, "Error\nin L data: bad elements nb\n"), FAIL);
	if (check_fformat(&i, &commas, line))
		return (1);
	get_floats(line, &scn->light.pos, 'L');
	j = i;
	if (check_float_nb(&i, line))
		return (FAIL);
	scn->light.brightness = ft_atof(line + j);
	if (float_range_checker(scn->light.brightness, 0.0f, 1.0f, TRUE) == FALSE)
		return (ft_fprintf(2, "Error\nin L data: value not in [0;1]\n"), FAIL);
	if (check_rgb(line + i) == SUCCESS)
		scn->light.color = atorgb(line + i);
	else
		return (FAIL);
	return (SUCCESS);
}
