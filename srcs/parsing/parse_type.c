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
	int		i;
	char	**ptr;

	i = 0;
	if (count_element(line) != 2)
		return (ft_fprintf(2, "Error\nin A data: too much data\n"), FAIL);
	ptr = ft_split(line, ' ');
	if (!ptr)
		return (ft_fprintf(2, "Error\nmalloc error"), FAIL);
	if (check_float_nb(ptr[0]))
		return (ft_free_split(ptr), FAIL);
	scn->alight.al = ft_atof(ptr[0]);
	if (float_range_checker(scn->alight.al, 0.0f, 1.0f, TRUE) == FALSE)
		return (ft_free_split(ptr), ft_fprintf(2, "Error\nin A data\n"), FAIL);
	if (check_rgb(ptr[1]) == SUCCESS)
	{
		scn->alight.color = atorgb(line + i);
	}
	else
		return (ft_free_split(ptr), FAIL);
	// TODO : remove:
	printf("A:\nal: %f\nrgb: %d, %d, %d\n", scn->alight.al, get_r(scn->alight.color), get_g(scn->alight.color), get_b(scn->alight.color));
	return (ft_free_split(ptr), SUCCESS);
}

int get_infos_c(char *line, t_scene *scn)
{
	int	i;
	int	commas;
	char	**ptr;

	if (count_element(line) != 3)
		return (ft_fprintf(2, "Error\nin C data, bad elements nb\n"), FAIL);
	ptr = ft_split(line, ' ');
	if (!ptr)
		return (ft_fprintf(2, "Error\n malloc error in C parse"), FAIL);
	if (check_fformat(&i, &commas, ptr[0]))
		return (ft_free_split(ptr), FAIL);
	get_floats(ptr[0], &scn->cam.pos, 'C');
	if (check_fformat(&i, &commas, ptr[1]))
		return (ft_free_split(ptr), FAIL);
	if (get_floats(ptr[1], &scn->cam.orientation, 'c'))
		return (ft_free_split(ptr), FAIL);
	if (check_float_nb(ptr[2]))
		return (ft_free_split(ptr), FAIL);
	scn->cam.fov_w = ft_atof(ptr[2]);
	if (!float_range_checker(scn->cam.fov_w, 0, 180, TRUE))
		return (ft_free_split(ptr), ft_fprintf(2, "Error\nin C: fov\n"), FAIL);
	// TODO : remove:
	printf("C:\npos: %f, %f, %f\norient: %f, %f, %f\nfov: %f\n", scn->cam.pos.x, scn->cam.pos.y, scn->cam.pos.z, scn->cam.orientation.x, scn->cam.orientation.y, scn->cam.orientation.z,
		   scn->cam.fov_w);
	return (ft_free_split(ptr), SUCCESS);
}

int get_infos_l(char *line, t_scene *scn)
{
	int		i;
	int		commas;
	char	**ptr;

	if (count_element(line) != 3)
		return (ft_fprintf(2, "Error\nin L data: bad elements nb\n"), FAIL);
	ptr = ft_split(line, ' ');
	if (!ptr)
		return (ft_fprintf(2, "Error\n malloc error in L parse"), FAIL);
	if (check_fformat(&i, &commas, ptr[0]))
		return (ft_free_split(ptr), FAIL);
	get_floats(ptr[0], &scn->light.pos, 'L');
	if (check_float_nb(ptr[1]))
		return (ft_free_split(ptr), FAIL);
	scn->light.brightness = ft_atof(ptr[1]);
	if (float_range_checker(scn->light.brightness, 0.0f, 1.0f, TRUE) == FALSE)
		return (ft_free_split(ptr), ft_fprintf(2, "Error\nin L data\n"), FAIL);
	if (check_rgb(ptr[2]) == SUCCESS)
		scn->light.color = atorgb(ptr[2]);
	else
		return (ft_free_split(ptr), FAIL);
	// TODO : remove:
	printf("L:\npos: %f, %f, %f\nbrightness: %f\nrgb: %d, %d, %d\n", scn->light.pos.x, scn->light.pos.y, scn->light.pos.z, scn->light.brightness,
		   get_r(scn->light.color), get_g(scn->light.color), get_b(scn->light.color));
	return (ft_free_split(ptr), SUCCESS);
}
