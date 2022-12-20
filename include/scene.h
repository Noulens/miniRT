/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:57:36 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 07:47:20 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "math_func.h"

typedef struct s_object
{
	t_vec	pos;
	t_vec	translate;
	t_vec	rotate;
	int		color;
}	t_object;

typedef struct s_cam{
	t_vec	pos;
	t_vec	translate;
	t_vec	rotate;
	int		fov;
	int		focal_length;
}	t_cam;

typedef struct s_scene
{
	int			win_w;
	int			win_h;
	double		canvas_ratio;
	int			num_objects_in_scene;
	t_object	*objects;
	t_cam		cam;
	int			bg_color;
}	t_scene;

typedef struct s_ray
{

}	t_ray;

int	render(t_img *img, t_scene *scene);

#endif