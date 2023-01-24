/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/23 18:30:11 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	hit_normal_sphere(t_surfaceinfo *info, t_stdobj *obj)
{
	t_sp		*sphere;

	sphere = (t_sp *)obj->obj;
	info->hit_normal = vec_normalize(vec_sub(info->hit_point, sphere->pos));
	info->hit_uv.x = (1 + atan2(info->hit_normal.z, \
	info->hit_normal.x) / M_PI) * 0.5;
	info->hit_uv.y = acosf(info->hit_normal.y) / M_PI;
	info->hit_uv.z = 0;
}

void	hit_normal_plane(t_surfaceinfo *info, t_stdobj *obj)
{
	t_pl		*plane;

	plane = (t_pl *)obj->obj;
	info->hit_normal = vec_normalize(plane->orientation);
}

void	hit_normal_cyl(t_surfaceinfo *info, t_stdobj *obj)
{
	t_cy	*cyl;
	float	t;
	t_vec3	pt;
	t_vec3	top;
	t_vec3	bom;

	cyl = (t_cy *)obj->obj;
	top = vec_add(cyl->pos, vec_scale(cyl->orientation, cyl->height / 2.0f));
	bom = vec_sub(cyl->pos, vec_scale(cyl->orientation, cyl->height / 2.0f));
	if (vec_length(vec_sub(info->hit_point, top)) < cyl->diameter / 2)
		info->hit_normal = cyl->orientation;
	else if (vec_length(vec_sub(info->hit_point, bom)) < cyl->diameter / 2)
		info->hit_normal = vec_scale(cyl->orientation, -1.0f);
	else
	{
		t = vec_dot(vec_sub(info->hit_point, cyl->pos), cyl->orientation);
		pt = vec_add(cyl->pos, vec_scale(cyl->orientation, t));
		info->hit_normal = vec_normalize(vec_sub(info->hit_point, pt));
	}
}

t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	info->view_dir = vec_normalize(vec_scale(ray.dir, -1));
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	if (obj->objtp == 0)
		hit_normal_sphere(info, obj);
	if (obj->objtp == 2)
		hit_normal_plane(info, obj);
	if (obj->objtp == 1)
		hit_normal_cyl(info, obj);
	return (info);
}

int	compute_pixel(t_scene *s, int i, int j, t_func *inter)
{
	t_ray			ray;
	int				closest_obj;
	int				hit_color;
	t_surfaceinfo	info;

	closest_obj = -1;
	s->x = i;
	s->y = j;
	ray = build_camera_ray(s, i, j);
	closest_obj = find_closest_obj(s, ray, inter, &info.hit_dist);
	if (closest_obj != -1)
	{
		get_surfaceinfo(&info, s->objtab[closest_obj], ray);
		if (s->objtab[closest_obj]->objtp == 0 \
		|| s->objtab[closest_obj]->objtp == 2 || s->objtab[closest_obj]->objtp == 1)
		{
			hit_color = shading(s, &info, closest_obj, inter);
			my_mlx_pixel_put(s->ig, i, j, hit_color);
		}
		else
			my_mlx_pixel_put(s->ig, i, j, s->objtab[closest_obj]->metacolor);
	}
	else
		my_mlx_pixel_put(s->ig, i, j, s->bg_color);
	return (closest_obj);
}

int	render(t_scene *scene, t_func *inter)
{
	int	i;
	int	j;

	j = -1;
	while (++j < scene->win_h)
	{
		i = -1;
		while (++i < scene->win_w)
		{
			compute_pixel(scene, i, j, inter);
		}
	}
	return (0);
}
