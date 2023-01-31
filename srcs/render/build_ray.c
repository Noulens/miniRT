/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:24:56 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 11:07:11 by hyunah           ###   ########.fr       */
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
	return (mul_mat(mul_mat(mul_mat(t[T], t[RX]), t[RY]), t[RZ]));
}

t_ray	orient_camera(t_scene *scene, t_vec3 *pixel_camera)
{
	t_ray	oriented_ray;

	*pixel_camera = from_two_vec_do_rotation(set_vec(0, 0, -1), \
	scene->cam.orientation, *pixel_camera);
	oriented_ray.origin = set_vec(0, 0, 0);
	oriented_ray.dir = vec_normalize(*pixel_camera);
	return (oriented_ray);
}

t_ray	build_camera_ray(t_scene *scene, int x, int y)
{
	t_ray	oriented_ray;
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
	pixel_camera.x = pixel_screenspace.x * scene->image_ratio * \
			scene->cam.fov_h_len;
	pixel_camera.y = pixel_screenspace.y * scene->cam.fov_h_len;
	pixel_camera.z = -1;
	oriented_ray = orient_camera(scene, &pixel_camera);
	matrix_vec_mult(set_transform2(&scene->cam.translate, \
	&scene->cam.rotate), &oriented_ray.origin);
	matrix_vec_mult(set_transform2(&scene->cam.translate, \
	&scene->cam.rotate), &pixel_camera);
	oriented_ray.dir = vec_sub(pixel_camera, oriented_ray.origin);
	oriented_ray.dir = vec_normalize(oriented_ray.dir);
	return (oriented_ray);
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
