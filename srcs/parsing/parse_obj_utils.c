/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:11:11 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/28 14:11:13 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int parse_cy_2(char *line, t_cy *cylinder, int *j, t_scene *scn)
{
	line += *j;
	*j = 0;
	if (check_float_nb(j, line))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: hei\n"), FAIL);
	cylinder->height = ft_atof(line);
	if (check_rgb(line + *j))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: rgb\n"), FAIL);
	cylinder->color = atorgb(line + *j);
	if (objadd_front(&scn->objects, cylinder, CY))
		return (free(cylinder),ft_fprintf(2, "Error\nparse_cy: add\n"), FAIL);
	return (SUCCESS);
}
