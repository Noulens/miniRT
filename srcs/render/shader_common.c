/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:38:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/23 18:28:23 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	shadow_visibility(t_scene *s, t_func *inter, t_surfaceinfo *i, t_vec3 ldir)
{
	float	hit_dist;
	int		vis;
	t_ray	hit;

	hit.origin = vec_add(i->hit_point, vec_scale(i->hit_normal, 0.01f));
	hit.dir = vec_normalize(vec_scale(ldir, -1));
	vis = find_closest_obj(s, hit, inter, &hit_dist);
	if (hit_dist > vec_length(vec_sub(i->hit_point, s->lamptab[s->k]->pos)))
		return (1);
	if (vis == -1)
		return (1);
	else
		return (0);
}

void	get_pointl_info(t_scene *s, t_surfaceinfo *i, t_vec3 *dir, float *f)
{
	t_vec3	light_dir;
	float	r2;

	light_dir = vec_sub(i->hit_point, s->lamptab[s->k]->pos);
	r2 = vec_length(light_dir);
	*dir = vec_normalize(light_dir);
	*f = s->lamptab[k]->brightness / (4 * M_PI * r2);
}
