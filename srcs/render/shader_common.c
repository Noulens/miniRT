/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:38:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/01 09:54:47 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	shadow_vis(t_scene *s, t_func *inter, t_surfaceinfo *i, t_vec3 ldir)
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
	*f = s->lamptab[s->k]->brightness / (4 * M_PI * r2);
}

void	get_render_info(t_scene *s, t_surfaceinfo *i, int c_obj, t_material *m)
{
	m->l_inten = s->lamptab[s->k]->brightness;
	m->obj_color = vec_color(s->objtab[c_obj]->metacolor);
	get_pointl_info(s, i, &(m->l_dir), &m->l_inten);
	m->l_inten *= s->lamp->exposure;
	m->face_ratio = ft_max(0.0f, vec_dot(i->hit_normal, \
	vec_scale(m->l_dir, -1)));
}

void	keep_between_zero_one_vector(t_vec3 *v)
{
	keep_between_zero_one(&v->x);
	keep_between_zero_one(&v->y);
	keep_between_zero_one(&v->z);
}
