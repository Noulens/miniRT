/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/20 21:35:50 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "interaction.h"
#include "scene.h"
#include "math_func.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_cam	cam_init(t_scene *s)
{
	t_cam	*cam;
	double	tmp;

	cam = &s->cam;
	cam->pos = set_vec(0, 0, 0);
	cam->orientation = set_vec(0, 0, -1);
	cam->fov_w = 70;
	tmp = tan(to_radian((double)cam->fov_w / 2));
	cam->fov_h_len = 2 * tmp / s->image_ratio;
	cam->fov_h = (int)to_degree(atan(cam->fov_h_len / 2)) * 2;
	// we would need this to do translation. codes are written but never tested yet.
	// cam->translate = set_vec(0, 0, 0);
	// cam->rotate = set_vec(0, 0, 0);
	// matrix_transformation(&cam->pos, cam->translate, cam->rotate);
	return (*cam);
}

t_scene	scene_init(t_scene *s)
{
	s->win_w = 198;
	s->win_h = 102;
	s->image_ratio = (double)s->win_w / (double)s->win_h;
	// I'm not sure if we need to calculate this. would it be useful in the future?
	// s->cam.focal_length = (s->win_w / 2) / tan(to_radian((s->cam.fov / 2)));
	s->bg_color = create_trgb(255, 255, 255, 255);
	cam_init(s);
	return (*s);
}

void	win_launcher(void)
{
	t_scene	scene;
	t_img	img;

	img.mlx = mlx_init();
	if (!img.mlx)
		exit(EXIT_FAILURE);
	scene = scene_init(&scene);
	img.win = mlx_new_window(img.mlx, scene.win_w, scene.win_h, "miniRT");
	img.img = mlx_new_image(img.mlx, scene.win_w, scene.win_h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	// mlx_key_hook(win, ft_key, &img);
	render(&img, &scene);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 17, 1L << 17, ft_closebutton, &img);
	mlx_hook(img.win, 2, 1L << 0, ft_key, &img);
	mlx_loop(img.mlx);
}
