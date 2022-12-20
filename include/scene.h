/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:57:36 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 18:05:38 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "math_func.h"
# include "init.h"

typedef struct s_object
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
}	t_object;

typedef struct s_cam{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	t_vec3	orientation;
	int		fov_w;
	int		fov_h;
	double	fov_h_len;
	double	focal_length;
}	t_cam;

typedef struct s_light
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
	double	brightness;
}	t_light;

typedef struct s_scene
{
	int			win_w;
	int			win_h;
	double		image_ratio;
	int			num_objects_in_scene;
	t_object	*objects;
	t_cam		cam;
	int			bg_color;
}	t_scene;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

#endif