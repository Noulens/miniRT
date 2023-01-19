/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/19 17:40:08 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	shadow_visibility(t_scene *scene, t_func *inter, t_surfaceinfo *info, t_vec3 light_dir)
{
	float	hit_dist;
	int		vis;
	t_ray	hit;

	hit.origin = vec_add(info->hit_point, vec_scale(info->hit_normal, 0.01f));
	hit.dir = vec_normalize(vec_scale(light_dir, -1));
	vis = find_closest_obj(scene, hit, inter, &hit_dist);
	if (vis == -1)
		return (1);
	else
		return (0);
}

void	get_pointlight_info(t_scene *scene, t_surfaceinfo *info, t_vec3 *dir, float *intensity)
{
	t_vec3	light_dir;
	float	r2;

	light_dir = vec_sub(info->hit_point, scene->light.pos);
	r2 = vec_length(light_dir);
	*dir = vec_normalize(light_dir);
	*intensity = scene->light.brightness / (4 * M_PI * r2);
	// printf("scene->light.brightness: %f\n", scene->light.brightness);
	// printf("( 4 * M_PI * r2): %f\n", ( 4 * M_PI * r2));
	// printf("intensity: %f\n", *intensity);
	// printf("\n");
}

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	float	light_intensity;
	float	exposure;
	int		vis;
	t_vec3	obj_color;
	t_vec3	diffuse;
	t_vec3	light_dir;

	exposure = 30;
	light_intensity = scene->light.brightness;
	light_dir = set_vec(0, -1, 0);
	obj_color = vec_scale(vec_color(scene->objtab[c_obj]->metacolor), 1 / M_PI);
	get_pointlight_info(scene, info, &light_dir, &light_intensity);
	light_intensity *= exposure;
	vis = shadow_visibility(scene, inter, info, light_dir);
	diffuse = vec_scale(vec_color(scene->light.color), light_intensity);
	diffuse = vec_scale(vec_scale(vec_mult(obj_color, diffuse), vis), \
	ft_max(0.0f, vec_dot(info->hit_normal, vec_scale(light_dir, -1))));
	return (int_color(diffuse));
}