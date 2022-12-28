/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/23 17:14:23 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	cam_init(t_scene *s)
{
	float	fov_w_half_len;

	//cam = &s->cam;
	//cam->pos = set_vec(0, 0, 0);
	//cam->orientation = set_vec(0, 0, -1);
	//s->cam.fov_w = 70;
	fov_w_half_len = tanf(to_radian(s->cam.fov_w / 2));
	s->cam.fov_h_len = 2 * fov_w_half_len / s->image_ratio;
	s->cam.fov_h = (int)to_degree(atanf(s->cam.fov_h_len / 2)) * 2;
	s->cam.translate = set_vec(0, 0, 0);
	s->cam.rotate = set_vec(0, 0, 0);
	// we would need this to do translation. codes are written but never tested yet.
	// matrix_transformation(&cam->pos, cam->translate, cam->rotate);
	//return (*cam);
}

void	scene_init(t_scene *s)
{
	s->win_w = 192;
	s->win_h = 108;
	s->image_ratio = (float)s->win_w / (float)s->win_h;
	// I'm not sure if we need to calculate this. would it be useful in the future?
	// s->cam.focal_length = (s->win_w / 2) / tan(to_radian((s->cam.fov / 2)));
	s->bg_color = ft_trgb(255, 0, 0, 0);
	cam_init(s);
}
