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
	int 	commas;
	t_cy	*cylinder;

	(void)scn;
	line += 2;
	cylinder = (t_cy *)malloc(sizeof(t_cy));
	if (!cylinder)
		return (ft_fprintf(2, "Error\nmalloc error in parse cylinder\n"), FAIL);
	if (check_fformat(&i, &commas, line))
		return (ft_fprintf(2, "Error\ncylinder position\n"), FAIL);
	get_floats(line, &cylinder->pos, 'P');
	line += i;
	if (check_fformat(&i, &commas, line))
		return (free(cylinder), ft_fprintf(2, "Error\ncylinder orientation\n"), FAIL);
	get_floats(line, &cylinder->orientation, 'O');
	line += i;
	if (check_float_nb(&i, line))

	if (check_rgb(line))
		return (FAIL);
	cylinder->color = atorgb(line);
	return (SUCCESS);
}

int parse_sp(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
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
