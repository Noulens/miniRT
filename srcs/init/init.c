/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2023/02/02 17:02:45 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	cam_init(t_scene *s)
{
	float	fov_w_half_len;

	fov_w_half_len = tanf(to_radian(s->cam.fov_w / 2));
	s->cam.fov_h_len = 2 * fov_w_half_len / s->image_ratio;
	s->cam.fov_h = to_degree(atanf(s->cam.fov_h_len / 2)) * 2;
	s->cam.rotate = set_vec(0, 0, 0);
}

void	scene_init(t_scene *s)
{
	s->win_w = 980;
	s->win_h = 545;
	s->image_ratio = (float)s->win_w / (float)s->win_h;
	s->cam.focal_length = ((float)s->win_w / 2)
		/ tanf(to_radian((s->cam.fov_w / 2)));
	s->bg_color = ft_trgb(255, 0, 0, 0);
	s->lamp->exposure = 20;
	s->k = 0;
	cam_init(s);
}

void	scenevarinit(t_scene *s)
{
	s->objects = NULL;
	s->target = -1;
	s->target_light = -1;
	s->objtab = NULL;
	s->lamp = NULL;
	s->lamptab = NULL;
	s->msg = "camera : [C], light : [L], object : click object, \
	copy : [T], save param : [Y]";
	set_identity(&s->fwtfm);
}
