/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:44:38 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/23 14:29:31 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_element(char *line)
{
	int	word_flag;
	int	i;
	int	word_count;

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
	char	**ptr;
	float	x;
	float	y;
	float	z;

	ptr = ft_split(line, ',');
	if (!ptr)
		return (ft_fprintf(2, "Error\nbad malloc get_floats\n"));
	if (ft_ptrlen((const char **)ptr) != 3)
		return (ft_free_split(ptr), ft_fprintf(2, "Error\nbad coord\n"));
	x = ft_atof(ptr[0]);
	y = ft_atof(ptr[1]);
	z = ft_atof(ptr[2]);
	if (mode == 'O')
	{
		if ((!x && !y && !z) || !float_range_checker(x, -1.0f, 1.0f, TRUE)
			|| !float_range_checker(y, -1.0f, 1.0f, TRUE)
			|| !float_range_checker(z, -1.0f, 1.0f, TRUE))
			return (ft_free_split(ptr), FAIL);
		*vector = vec_normalize(set_vec(x, y, z));
		return (ft_free_split(ptr), SUCCESS);
	}
	*vector = set_vec(x, y, z);
	return (ft_free_split(ptr), SUCCESS);
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
			continue ;
		}
		else if (line[*i] == '.')
		{
			if (check_decimal(i, line))
				return (FAIL);
			if (line[*i] == ',')
			{
				inc_iter(i, commas);
				continue ;
			}
			else if (line[*i] == ',')
				++*commas;
		}
	}
	return (*commas != 2);
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
	int	i;

	i = 0;
	if (line[i] == '-')
		i++;
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
