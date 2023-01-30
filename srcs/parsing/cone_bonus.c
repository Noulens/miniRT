/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:00:04 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/18 13:00:09 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_co_2(char **ptr, t_co *cone, t_scene *scn)
{
	if (check_float_nb(ptr[3]))
		return (free(cone), ft_fprintf(2, "Error\nparse_co: hei\n"), FAIL);
	cone->height = ft_atof(ptr[3]);
	if (check_rgb(ptr[4]))
		return (free(cone), ft_fprintf(2, "Error\nparse_co: rgb\n"), FAIL);
	cone->color = atorgb(ptr[4]);
	if (objadd_front(&scn->objects, cone, CO, cone->color))
		return (free(cone), ft_fprintf(2, "Error\nparse_co: add\n"), FAIL);
	return (SUCCESS);
}

int	parse_co(char *line, t_scene *scn)
{
	int		i;
	int		commas;
	t_co	*cone;
	char	**ptr;

	if (count_element(line) != 5)
		return (ft_fprintf(2, "Error\nin CO data: bad elements nb\n"), FAIL);
	cone = (t_co *)malloc(sizeof(t_co));
	if (!cone)
		return (ft_fprintf(2, "Error\nbad malloc in parse_co\n"), FAIL);
	ptr = ft_split(line, ' ');
	if (!ptr)
		return (free(cone), ft_fprintf(2, "Error\nbad malloc co\n"), FAIL);
	if (check_fformat(&i, &commas, ptr[0]))
		return (ft_free_split(ptr), free(cone), ft_fprintf(2, ERCO), FAIL);
	get_floats(ptr[0], &cone->pos, 'P');
	if (check_fformat(&i, &commas, ptr[1])
		|| get_floats(ptr[1], &cone->orientation, 'O'))
		return (ft_free_split(ptr), free(cone), ft_fprintf(2, ERO2), FAIL);
	if (check_float_nb(ptr[2]))
		return (ft_free_split(ptr), free(cone), ft_fprintf(2, ERO3), FAIL);
	cone->rad = ft_atof(ptr[2]) / 2.0f;
	if (parse_co_2(ptr, cone, scn))
		return (ft_free_split(ptr), FAIL);
	return (ft_free_split(ptr), SUCCESS);
}
