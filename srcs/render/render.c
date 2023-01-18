/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/18 15:42:29 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "math_func.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*offset;

	offset = data->addr + (y * data->line_length + x * (data->bpp >> 3));
	*(unsigned int *)offset = color;
}

t_matrix4	set_transform2(t_vec3 *trans, t_vec3 *rot)
{
	t_matrix4	t[4];
	int			i;

	i = -1;
	while (++i < 4)
		set_identity(&t[i]);
	t[T].m[0][3] = trans->x;
	t[T].m[1][3] = trans->y;
	t[T].m[2][3] = trans->z;

	t[RZ].m[0][0] = cosf(to_radian(rot->z));
	t[RZ].m[0][1] = -sinf(to_radian(rot->z));
	t[RZ].m[1][0] = sinf(to_radian(rot->z));
	t[RZ].m[1][1] = cosf(to_radian(rot->z));
	t[RY].m[0][0] = cosf(to_radian(rot->y));
	t[RY].m[0][2] = sinf(to_radian(rot->y));
	t[RY].m[2][0] = -sinf(to_radian(rot->y));
	t[RY].m[2][2] = cosf(to_radian(rot->y));
	t[RX].m[1][1] = cosf(to_radian(rot->x));
	t[RX].m[1][2] = -sinf(to_radian(rot->x));
	t[RX].m[2][1] = sinf(to_radian(rot->x));
	t[RX].m[2][2] = cosf(to_radian(rot->x));
	// matrix_print(t[RY], 1);
	return (mul_mat(mul_mat(mul_mat(t[T], t[RX]), t[RY]), t[RZ]));
}

t_ray	build_camera_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_raster;
	t_vec3	pixel_ndc;
	t_vec3	pixel_screenspace;
	t_vec3	pixel_camera;

	pixel_raster.x = (float)x + 0.5f;
	pixel_raster.y = (float)y + 0.5f;
	pixel_ndc.x = pixel_raster.x / (float)scene->win_w;
	pixel_ndc.y = pixel_raster.y / (float)scene->win_h;
	pixel_screenspace.x = 2.0f * pixel_ndc.x - 1.0f;
	pixel_screenspace.y = 1.0f - (2.0f * pixel_ndc.y);

	ray.origin = set_vec(0, 0, 0);
	pixel_camera.x = pixel_screenspace.x * scene->image_ratio * \
			scene->cam.fov_h_len;
	pixel_camera.y = pixel_screenspace.y * scene->cam.fov_h_len;
	pixel_camera.z = -1;
	// pixel_camera = set_vec(1, 0, 0);

	t_vec3	rot;
	t_vec3	trans;

	trans = set_vec(1, 10, 1);
	rot = set_vec(-90, 0, 0);
	matrix_vec_mult(set_transform2(&trans, &rot), &ray.origin);
	matrix_vec_mult(set_transform2(&trans, &rot), &pixel_camera);

	// pixel_camera.x = pixel_screenspace.x * scene->image_ratio * 
	// 		scene->cam.fov_h_len;
	// pixel_camera.y = pixel_screenspace.y * scene->cam.fov_h_len;
	// pixel_camera.z = -1;
	// pixel_camera = vec_add(pixel_camera, scene->cam.pos);
	// ray.origin = scene->cam.pos;
	ray.dir = vec_sub(pixel_camera, ray.origin);
	ray.dir = vec_normalize(ray.dir);
	return (ray);
}

int	find_closest_obj(t_scene *scene, t_ray ray, t_func *inter, float *closest)
{
	int		k;
	int		closest_obj;
	float	closest_distance;
	float	hit_dist;

	k = -1;
	closest_obj = -1;
	closest_distance = INFINITY;
	while (++k < scene->num_objects_in_scene)
	{
		if ((*inter)[scene->objtab[k]->objtp](ray, scene->objtab[k], &hit_dist))
		{
			if (closest_distance > hit_dist)
			{
				closest_distance = hit_dist;
				closest_obj = k;
			}
		}
	}
	*closest = closest_distance;
	return (closest_obj);
}

int	compute_pixel(t_scene *s, int i, int j, t_func *inter)
{
	t_ray			ray;
	int				closest_obj;
	int				hit_color;
	t_surfaceinfo	info;

	info.hit_dist = 0;
	closest_obj = -1;
	ray = build_camera_ray(s, i, j);
	closest_obj = find_closest_obj(s, ray, inter, &info.hit_dist);
	if (closest_obj != -1)
	{
		get_surfaceinfo(&info, s->objtab[closest_obj], ray);
		if (s->objtab[closest_obj]->objtp == 0 \
		|| s->objtab[closest_obj]->objtp == 2)
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
/*
	if (x == 0 && y == 0){
	printf("pixel camera vec when 0,0:");
	print_vec(&pixel_camera);
	}
	pixel_camera = vec_add(pixel_camera, scene->cam.pos);
	if (x == 0 && y == 0){
	printf("camera pos when 0,0:");
	print_vec(&scene->cam.pos);
	}
	t_vec3 r;
	r = vec_add(scene->cam.orientation, set_vec(0, 0, -1));
	if (x == 0 && y == 0){
	printf("cam.orientation : ");
	print_vec(&scene->cam.orientation);
	printf("r : ");
	print_vec(&r);
	}
	// t_vec3 t;
	// if (x == 0 && y == 0){
	// printf("cam orientation:");
	// print_vec(&scene->cam.orientation);
	// }
	// r = vec_sub(scene->cam.orientation, set_vec(0, 0, -1));
	// r = vec_normalize(scene->cam.orientation);
	// if (x == 0 && y == 0){
	// printf("vec:");
	// 	print_vec(&r);
	// // }
	// t = set_vec(0, 0, 0);
	// r = set_vec(0, 0, 0);
	// matrix_vec_mult(set_transform2(&t, &r), &pixel_camera);
*/