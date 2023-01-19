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
	cone->diameter = ft_atof(ptr[2]);
	if (parse_co_2(ptr, cone, scn))
		return (ft_free_split(ptr), FAIL);
	return (ft_free_split(ptr), SUCCESS);
}

static void	check_for_solutions_cone(float *dist)
{
	if (dist[ROOT1] > dist[ROOT2])
		ft_swap(&dist[ROOT1], &dist[ROOT2]);
	if (dist[ROOT1] < 0 && dist[ROOT2] > 0)
		dist[RES] = dist[ROOT2];
	else if (dist[ROOT1] > 0 && dist[ROOT2] > 0)
		dist[RES] = dist[ROOT1];
	else
	{
		dist[ROOT1] = 0;
		dist[ROOT2] = 0;
		dist[RES] = INFINITY;
	}
}

int	intersect_cone(t_ray ray, t_stdobj *obj, float *dist)
{
	float	qd[7];
	t_co	*co;

	co = (t_co *)obj->obj;
	qd[A] = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y
		- (ray.dir.z * ray.dir.z);
	qd[B] = 2 * ray.dir.x * (ray.origin.x - co->pos.x)
		+ 2 * ray.dir.y * (ray.origin.y - co->pos.y) - 2
		* ray.dir.z * (ray.origin.z - co->pos.z);
	qd[C] = (ray.origin.x - co->pos.x) * (ray.origin.x - co->pos.x)
		+ (ray.origin.y - co->pos.y) * (ray.origin.y - co->pos.y)
		- (ray.origin.z - co->pos.z) * (ray.origin.z - co->pos.z);
	qd[DELTA] = (qd[B] * qd[B]) - (4 * qd[A] * qd[C]);
	if (qd[DELTA] > 0)
	{
		qd[ROOT1] = (((-1 * qd[B] - sqrtf(qd[DELTA]))) / (2 * qd[A]));
		qd[ROOT2] = (((-1 * qd[B] + sqrtf(qd[DELTA]))) / (2 * qd[A]));
		check_for_solutions_cone(qd);
		*dist = qd[RES];
		return (1);
	}
	return (0);
}
