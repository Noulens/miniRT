/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:12:13 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 22:42:32 by waxxy            ###   ########.fr       */
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
		return (ft_fprintf(2, "l1 Error in A data: rgb not valid"), 1);
	++i;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' || i > 7)
		return (ft_fprintf(2, "l2 Error in A data: rgb not valid"), 1);
	if (!ft_isdigit(str[++i]))
		return (ft_fprintf(2, "l3 Error in A data: rgb not valid"), 1);
	while (ft_isdigit(str[i]))
		i++;
	if (i > 11)
		return (ft_fprintf(2, "l4 Error in A data: rgb not valid"), 1);
	while (str[++i] != '\0')
		if (!ft_isspace(str[i]))
			return (ft_fprintf(2, "l5 Error in A data: rgb not valid"), 1);
	return (SUCCESS);
}

int	atorgb(char *line, t_scene *scn)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (line[i] == ' ')
		++i;
	r = ft_atoi(line + i);
	if (r > 255 || r < 0)
		return (ft_fprintf(2, "Error in A data: rgb not in range"), 1);
	while (line[i] != ',')
		++i;
	g = ft_atoi(line + ++i);
	if (g > 255 || g < 0)
		return (ft_fprintf(2, "Error in A data: rgb not in range"), 1);
	while (line[i] != ',')
		++i;
	b = ft_atoi(line + ++i);
	if (b > 255 || b < 0)
		return (ft_fprintf(2, "Error in A data: rgb not in range"), 1);
	scn->alight.color = ft_trgb(255, r, g, b);
	return (0);
}

int	get_infos_a(char *line, t_scene *scn)
{
	int	i;

	i = 0;
	while (line[i] != '.')
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			return (ft_fprintf(2, "Error in A data: check ratio"), 1);
		++i;
	}
	while (line[++i] != ' ')
		if (!ft_isdigit(line[i]))
			return (ft_fprintf(2, "Error in A data: check ratio"), 1);
	scn->alight.al = ft_atof(line);
	if (float_range_checker(scn->alight.al, 0.0f, 1.0f, TRUE) == FALSE)
		return (ft_fprintf(2, "Error in A data: value not in [0;1]"), 1);
	if (check_rgb(line + i) == SUCCESS)
	{
		if (atorgb(line + i, scn))
			return (FAIL);
	}
	else
		return (FAIL);
	return (SUCCESS);
}

int get_infos_c(char *line, t_scene *scn)
{
	(void)scn;
	while (*line == ' ')
		++line;
	return (SUCCESS);
}

int get_infos_l(char *line, t_scene *scn)
{
	(void)scn;
	while (*line == ' ')
		++line;
	return (SUCCESS);
}
