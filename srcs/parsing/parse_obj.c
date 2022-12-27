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

	line++, line++;
	plan = (t_pl *)malloc(sizeof(t_pl));
	if (!plan)
		return (ft_fprintf(2, "Error\nmalloc error in parse plan\n"), 1);
	if (check_fformat(&i, &commas, line))
		return (ft_fprintf(2, RED"Error\nplan position\n"RESET), 1);
	get_floats(line, &plan->pos, 'P');
	line += i;
	if (check_fformat(&i, &commas, line))
		return (ft_fprintf(2, RED"Error\nplan orientation\n"RESET), 1);
	get_floats(line, &plan->orientation, 'O');
	line += i;
	if (check_rgb(line))
		return (1);
	plan->color = atorgb(line);
	if (objadd_front(&scn->objects, plan, PL))
		return (1);
	//scn->objects->obj = (t_pl *)scn->objects->obj;
	//printf("coord: %f, %f, %f\norientation %f, %f, %f", );
	return (0);
}

int parse_cy(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (0);
}

int parse_sp(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (0);
}

int parse_hy(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (0);
}

int parse_co(char *line, t_scene *scn)
{
	(void)scn;
	(void)line;
	return (0);
}
