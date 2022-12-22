/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/22 08:50:53 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_cam	cam_init(t_scene *s)
{
	t_cam	*cam;
	double	fov_w_half_len;

	cam = &s->cam;
	cam->pos = set_vec(0, 0, 0);
	cam->orientation = set_vec(0, 0, -1);
	cam->fov_w = 70;
	fov_w_half_len = tan(to_radian((double)cam->fov_w / 2));
	cam->fov_h_len = 2 * fov_w_half_len / s->image_ratio;
	cam->fov_h = (int)to_degree(atan(cam->fov_h_len / 2)) * 2;
	// we would need this to do translation. codes are written but never tested yet.
	// cam->translate = set_vec(0, 0, 0);
	// cam->rotate = set_vec(0, 0, 0);
	// matrix_transformation(&cam->pos, cam->translate, cam->rotate);
	return (*cam);
}

t_scene	scene_init(t_scene *s)
{
	s->win_w = 192;
	s->win_h = 108;
	s->image_ratio = (double)s->win_w / (double)s->win_h;
	// I'm not sure if we need to calculate this. would it be useful in the future?
	// s->cam.focal_length = (s->win_w / 2) / tan(to_radian((s->cam.fov / 2)));
	s->bg_color = ft_trgb(255, 255, 255, 255);
	cam_init(s);
	return (*s);
}
