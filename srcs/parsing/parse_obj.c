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

	line += 2;
	plan = (t_pl *)malloc(sizeof(t_pl));
	if (!plan)
		return (ft_fprintf(2, "Error\nmalloc error in parse plan\n"), FAIL);
	if (check_fformat(&i, &commas, line))
		return (ft_fprintf(2, "Error\nplan position\n"), FAIL);
	get_floats(line, &plan->pos, 'P');
	line += i;
	if (check_fformat(&i, &commas, line))
		return (free(plan), ft_fprintf(2, "Error\nplan orientation\n"), FAIL);
	get_floats(line, &plan->orientation, 'O');
	line += i;
	if (check_rgb(line))
		return (FAIL);
	plan->color = atorgb(line);
	//printf("coord: %f, %f, %f\n", plan->pos.x, plan->pos.y, plan->pos.z);
	//printf("orientation %f, %f, %f\n", plan->orientation.x, plan->orientation.y, plan->orientation.z);
	//printf("color: %u\n", plan->color);
	if (objadd_front(&scn->objects, plan, PL))
		return (free(plan), FAIL);
	return (SUCCESS);
}

int parse_cy(char *line, t_scene *scn)
{
	int 	i;
	int 	j;
	int 	commas;
	t_cy	*cylinder;

	line += 2;
	cylinder = (t_cy *)malloc(sizeof(t_cy));
	if (!cylinder)
		return (ft_fprintf(2, "Error\nbad malloc in parse_cy\n"), FAIL);
	if (check_fformat(&i, &commas, line))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: pos\n"), FAIL);
	get_floats(line, &cylinder->pos, 'P');
	line += i;
	if (check_fformat(&i, &commas, line)
		|| get_floats(line, &cylinder->orientation, 'O'))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: or.\n"), FAIL);
	line += i;
	j = 0;
	if (check_float_nb(&j, line))
		return (free(cylinder), ft_fprintf(2, "Error\nparse_cy: dia\n"), FAIL);
	cylinder->diameter = ft_atof(line);
	if (parse_cy_2(line, cylinder, &j, scn))
		return (FAIL);
	return (SUCCESS);
}

int parse_sp(char *line, t_scene *scn)
{
	int 	i;
	int 	j;
	int		commas;
	t_sp	*sphere;

	line += 2;
	sphere = (t_sp *)malloc(sizeof(t_sp));
	if (!sphere)
		return (ft_fprintf(2, "Error\nbad malloc in parse_sp\n"), FAIL);
	if (check_fformat(&i, &commas, line))
		return (free(sphere), ft_fprintf(2, "Error\nparse_sp: pos\n"), FAIL);
	get_floats(line, &sphere->pos, 'P');
	line += i;
	j = 0;
	if (check_float_nb(&j, line))
		return (free(sphere), ft_fprintf(2, "Error\nparse_sp: dia\n"), FAIL);
	sphere->diameter = ft_atof(line);
	line += j;
	if (check_rgb(line))
		return (free(sphere), ft_fprintf(2, "Error\nparse_sp: rgb\n"), FAIL);
	sphere->color = atorgb(line);
	if (objadd_front(&scn->objects, sphere, CY))
		return (free(sphere), ft_fprintf(2, "Error\nparse_sp: add\n"),  FAIL);
	//printf("pos: %f, %f, %f\ndia: %f\nrgb: %d, %d, %d", sphere->pos.x, sphere->pos.y, sphere->pos.z, sphere->diameter,
	//	   get_r(sphere->color), get_g(sphere->color), get_b(sphere->color));
	return (SUCCESS);
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
