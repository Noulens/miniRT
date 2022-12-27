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
	check_fformat(&i, &commas, line);
	get_floats(line, &plan->pos, 'P');
}

int parse_cy(char *line, t_scene *scn)
{
	;
}

int parse_sp(char *line, t_scene *scn)
{
	;
}

int parse_hy(char *line, t_scene *scn)
{
	;
}

int parse_co(char *line, t_scene *scn)
{
	;
}
