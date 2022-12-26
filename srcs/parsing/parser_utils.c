/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:14:54 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/22 19:43:44 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_iter(int *i, int *commas)
{
	*i = 0;
	*commas = 0;
}

void	inc_iter(int *i, int *commas)
{
	++*i;
	++*commas;
}

void	skip_spaces(int *i, char *line)
{
	while (line[*i] == ' ')
		++*i;
}

int	check_decimal(int *i, char *line)
{
	while (++*i, line[*i] != ',' && !ft_isspace(line[*i]))
	{
		if (!ft_isdigit(line[*i]))
			return (ft_fprintf(2, "Error\nin L data: brightness"), 1);
	}
	return (0);
}

int	check_int_part(int *i, int *commas, char *line)
{
	if (line[*i] == '-')
		++*i;
	while (line[*i] != '.' && line[*i] != ',')
	{
		if (!ft_isdigit(line[*i]))
		{
			if (line[*i] == ' ' && *commas == 2)
				break;
			return (ft_fprintf(2, "Error\nin L data: brightness"), 1);
		}
		++*i;
	}
	return (0);
}