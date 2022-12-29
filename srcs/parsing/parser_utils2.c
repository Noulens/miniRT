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

int	get_floats(char *line, t_vec3 *vector, char mode)
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
	if (mode == 'O')
	{
		if (!float_range_checker(x, -1.0f, 1.0f, TRUE)
			||!float_range_checker(y, -1.0f, 1.0f, TRUE)
			|| !float_range_checker(z, -1.0f, 1.0f, TRUE))
			return (FAIL);
	}
	*vector = set_vec(x, y, z);
	return (SUCCESS);
}

int	check_fformat(int *i, int *commas, char *line)
{
	init_iter(i, commas);
	while (line[*i])
	{
		if (check_int_part(i, commas, line))
			return (FAIL);
		if (line[*i] == ',')
		{
			inc_iter(i, commas);
			continue;
		}
		else if (line[*i] == '.')
		{
			if (check_decimal(i, line))
				return (FAIL);
			if (line[*i] == ',')
			{
				inc_iter(i, commas);
				continue;
			}
			else
				++*commas;
		}
	}
	return (SUCCESS);
}

static int	check_int_nb(int i, char *line)
{
	while (!ft_isspace(line[i]))
	{
		if (!ft_isdigit(line[i]))
			return (ft_fprintf(2, "Error\ncheck_int_nb\n"), FAIL);
		++i;
	}
	return (SUCCESS);
}

int	check_float_nb(char *line)
{
	int i;

	i = 0;
	if (ft_strchr(line, '.') == NULL)
		return (check_int_nb(i, line));
	while (line[i] != '.')
	{
		if (!ft_isdigit(line[i]))
			return (ft_fprintf(2, "Error\nin 1: check_float_nb\n"), FAIL);
		++i;
	}
	while (!ft_isspace(line[++i]))
	{
		if (!ft_isdigit(line[i]))
			return (ft_fprintf(2, "Error\nin 2: check_float_nb\n"), FAIL);
	}
	return (SUCCESS);
}
