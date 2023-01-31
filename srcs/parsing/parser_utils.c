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

int	check_decimal(int *i, char *line)
{
	while (++*i, line[*i] != ',' && !ft_isspace(line[*i]))
	{
		if (!ft_isdigit(line[*i]))
			return (ft_fprintf(2, "Error\nnot a good coord format\n"), FAIL);
	}
	return (SUCCESS);
}

int	check_int_part(int *i, int *commas, char *line)
{
	if (line[*i] == '-')
		++*i;
	if (!ft_isdigit(line[*i]))
	{
		return (ft_fprintf(2, "Error\nnot a good coord format\n"), FAIL);
	}
	while (line[*i] != '.' && line[*i] != ',')
	{
		if (!ft_isdigit(line[*i]))
		{
			if (*commas == 2)
				break ;
			return (ft_fprintf(2, "Error\nnot a good coord format\n"), FAIL);
		}
		++*i;
	}
	return (SUCCESS);
}
