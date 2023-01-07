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

int	parse_cy_2(char **ptr, t_cy *cylinder, t_scene *scn)
{
	if (check_float_nb(ptr[3]))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: hei\n"), FAIL);
	cylinder->height = ft_atof(ptr[3]);
	if (check_rgb(ptr[4]))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: rgb\n"), FAIL);
	cylinder->color = atorgb(ptr[4]);
	if (objadd_front(&scn->objects, cylinder, CY, cylinder->color))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: add\n"), FAIL);
	return (SUCCESS);
}
