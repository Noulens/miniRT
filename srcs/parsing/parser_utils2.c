/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:44:38 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/23 12:30:09 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_element(char *line)
{
	int word_flag;
	int i;
	int word_count;

	i = 0;
	word_flag = 0;
	word_count = 0;
	while (line && line[i])
	{
		if (ft_isspace(line[i]))
		{
			word_flag = 0;
			++i;
		}
		else if (word_flag == 1)
			++i;
		else
		{
			word_flag = 1;
			++word_count;
			++i;
		}
	}
	return (word_count);
}

int	get_floats(char *line, t_scene *scn, char mode)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 0;
	x = ft_atof(line);
	while (line[i] != ',')
		++i;
	y = ft_atof(line + ++i);
	while (line[i] != ',')
		++i;
	z = ft_atof(line + ++i);
	if (mode == 'L')
		scn->light.pos = set_vec(x, y, z);
	else if (mode == 'C')
		scn->cam.pos = set_vec(x, y, z);
	else if (mode == 'c' && float_range_checker(x, -1.0f, 1.0f, TRUE)
		&&float_range_checker(y, -1.0f, 1.0f, TRUE)
		&& float_range_checker(z, -1.0f, 1.0f, TRUE))
		scn->cam.orientation = set_vec(x, y, z);
	else
		return (1);
	return (0);
}

int	check_fformat(int *i, int *commas, char *line, t_scene *scn)
{
	(void)scn;
	init_iter(i, commas);
	skip_spaces(i, line);
	while (line[*i] != ' ')
	{
		if (check_int_part(i, commas, line))
			return (1);
		if (line[*i] == ',')
		{
			inc_iter(i, commas);
			continue;
		}
		else if (line[*i] == '.')
		{
			if (check_decimal(i, line))
				return (1);
			if (line[*i] == ',')
			{
				inc_iter(i, commas);
				continue;
			}
			else
				++*commas;
		}
	}
	return (0);
}

int	check_float_nb(int *i, char *line)
{
	if (ft_strchr(line, '.') == NULL)
		return (check_int_nb(i, line));
	while (line[*i] == ' ')
		++*i;
	while (line[*i] != '.')
	{
		if (!ft_isdigit(line[*i]) && line[*i] != ' ')
			return (ft_fprintf(2, "Error\nin 1 data: check float\n"), 1);
		++*i;
	}
	while (line[++*i] != ' ')
	{
		if (!ft_isdigit(line[*i]))
			return (ft_fprintf(2, "Error\nin 2 data: check float\n"), 1);
	}
	return (0);
}

int check_int_nb(int *i, char *line)
{
	while (line[*i] == ' ')
		++*i;
	while (!ft_isspace(line[*i]))
	{
		if (!ft_isdigit(line[*i]))
			return (ft_fprintf(2, "Error\nin data: check float\n"), 1);
		++*i;
	}
	return (0);
}
