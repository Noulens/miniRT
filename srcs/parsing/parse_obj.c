/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:32:49 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/27 16:32:52 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int parse_pl(char *line, t_scene *scn)
{
	int		i;
	int		commas;
	t_pl	*plan;
	char	**ptr;

	if (count_element(line) != 3)
		return (ft_fprintf(2, "Error\nin PL data: bad elements nb\n"), FAIL);
	plan = (t_pl *)malloc(sizeof(t_pl));
	ptr = ft_split(line, ' ');
	if (!plan || !ptr)
		return (ft_fprintf(2, "Error\nmalloc error in parse plan\n"), FAIL);
	if (check_fformat(&i, &commas, ptr[0]))
		return (ft_free_split(ptr), ft_fprintf(2, "Error\nplan pos\n"), FAIL);
	get_floats(ptr[0], &plan->pos, 'P');
	if (check_fformat(&i, &commas, ptr[1]))
		return (ft_free_split(ptr), free(plan), ft_fprintf(2, PLAN_ORI), FAIL);
	get_floats(ptr[1], &plan->orientation, 'O');
	if (check_rgb(ptr[2]))
		return (ft_free_split(ptr), FAIL);
	plan->color = atorgb(ptr[2]);
	printf("PL:\ncoord: %f, %f, %f\n", plan->pos.x, plan->pos.y, plan->pos.z);
	printf("orientation %f, %f, %f\n", plan->orientation.x, plan->orientation.y, plan->orientation.z);
	printf("color: %u\n", plan->color);
	if (objadd_front(&scn->objects, plan, PL))
		return (ft_free_split(ptr), free(plan), FAIL);
	return (ft_free_split(ptr), SUCCESS);
}

int parse_cy(char *line, t_scene *scn)
{
	int 	i;
	int 	commas;
	t_cy	*cylinder;
	char 	**ptr;

	if (count_element(line) != 5)
		return (ft_fprintf(2, "Error\nin CY data: bad elements nb\n"), FAIL);
	cylinder = (t_cy *)malloc(sizeof(t_cy));
	if (!cylinder)
		return (ft_fprintf(2, "Error\nbad malloc in parse_cy\n"), FAIL);
	ptr = ft_split(line, ' ');
	if (!ptr)
		return (free(cylinder), ft_fprintf(2, "Error\nbad malloc cy\n"), FAIL);
	if (check_fformat(&i, &commas, ptr[0]))
		return (ft_free_split(ptr), free(cylinder), ft_fprintf(2, ERCY), FAIL);
	get_floats(ptr[0], &cylinder->pos, 'P');
	if (check_fformat(&i, &commas, ptr[1])
		|| get_floats(ptr[1], &cylinder->orientation, 'O'))
		return (ft_free_split(ptr), free(cylinder), ft_fprintf(2, ERC2), FAIL);
	if (check_float_nb(ptr[2]))
		return (ft_free_split(ptr), free(cylinder), ft_fprintf(2, ERC3), FAIL);
	cylinder->diameter = ft_atof(ptr[2]);
	if (parse_cy_2(ptr, cylinder, scn))
		return (ft_free_split(ptr), FAIL);
	// TODO : remove :
	printf("CY:\npos: %f, %f, %f\norientation: %f, %f, %f\ndia: %f\nheight: %f\nrgb: %d, %d, %d\n", cylinder->pos.x, cylinder->pos.y, cylinder->pos.z, cylinder->orientation.x, cylinder->orientation.y, cylinder->orientation.z, cylinder->diameter, cylinder->height,
		   get_r(cylinder->color), get_g(cylinder->color), get_b(cylinder->color));
	return (ft_free_split(ptr), SUCCESS);
}

int parse_sp(char *line, t_scene *scn)
{
	int 	i;
	int		commas;
	t_sp	*sphere;
	char	**ptr;

	if (count_element(line) != 3)
		return (ft_fprintf(2, "Error\nin SP data: bad elements nb\n"), FAIL);
	sphere = (t_sp *)malloc(sizeof(t_sp));
	if (!sphere)
		return (ft_fprintf(2, "Error\nbad malloc sp\n"), FAIL);
	ptr = ft_split(line, ' ');
	if (!ptr)
		return (free(sphere), ft_fprintf(2, "Error\nbad malloc sp\n"), FAIL);
	if (check_fformat(&i, &commas, ptr[0]))
		return (ft_free_split(ptr), free(sphere), ft_fprintf(2, ERSPH1), FAIL);
	get_floats(ptr[0], &sphere->pos, 'P');
	if (check_float_nb(ptr[1]))
		return (ft_free_split(ptr), free(sphere), ft_fprintf(2, ERSPH2), FAIL);
	sphere->diameter = ft_atof(ptr[1]);
	if (check_rgb(ptr[2]))
		return (ft_free_split(ptr), free(sphere), ft_fprintf(2, ERSPH3), FAIL);
	sphere->color = atorgb(ptr[2]);
	if (objadd_front(&scn->objects, sphere, SP))
		return (ft_free_split(ptr), free(sphere), ft_fprintf(2, ERSPH),  FAIL);
	// TODO : remove :
	printf("SP:\npos: %f, %f, %f\ndia: %f\nrgb: %d, %d, %d", sphere->pos.x, sphere->pos.y, sphere->pos.z, sphere->diameter,
		   get_r(sphere->color), get_g(sphere->color), get_b(sphere->color));
	return (ft_free_split(ptr), SUCCESS);
}

int parse_hy(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (SUCCESS);
}

int parse_co(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (SUCCESS);
}
