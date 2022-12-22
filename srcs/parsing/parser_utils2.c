/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:44:38 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/22 22:12:18 by waxxy            ###   ########.fr       */
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
		if (line[i] == ' ')
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

int	get_floats(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (0);
}

int	check_fformat(int *i, int *commas, char *line, t_scene *scn)
{
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
	return (get_floats(line, scn));
}

int	check_float_nb(int *i, char *line)
{
	while (line[*i] == ' ')
		++*i;
	while (line[*i] != '.')
	{
		if (!ft_isdigit(line[*i]) && line[*i] != ' ')
			return (ft_fprintf(2, "Error in data: check float"), 1);
		++*i;
	}
	while (line[++*i] != ' ')
	{
		if (!ft_isdigit(line[*i]))
			return (ft_fprintf(2, "Error in data: check float"), 1);
	}
	return (0);
}
