/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_rend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:32:44 by waxxy             #+#    #+#             */
/*   Updated: 2023/02/02 17:08:46 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	clear_image(t_scene *scene)
{
	ft_bzero(scene->ig->addr, scene->win_w * scene->win_h * 4);
}

static void	init_intersect_fun(t_func *inter)
{
	(*inter)[0] = intersect_sphere;
	(*inter)[1] = intersect_cylinder;
	(*inter)[2] = intersect_plane_new;
	if (BONUS == TRUE)
		(*inter)[3] = intersect_cone;
}

void	win_launcher(t_scene *scene)
{
	t_img	img;
	t_func	intersect_func;

	scene->ig = &img;
	init_intersect_fun(&intersect_func);
	scene->func_ptr = &intersect_func;
	img.mlx = mlx_init();
	if (!img.mlx)
		return (ft_fprintf(2, "Error\nNo env\n"), des_minirt(scene), \
		exit(EXIT_FAILURE), (void)0);
	scene_init(scene);
	img.win = mlx_new_window(img.mlx, scene->win_w, scene->win_h, "miniRT");
	img.img = mlx_new_image(img.mlx, scene->win_w, scene->win_h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	render(scene, scene->func_ptr);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_string_put(img.mlx, img.win, 10, 10, -1, "MiniRT");
	mlx_string_put(img.mlx, img.win, 10, 25, -1, scene->msg);
	mlx_hook(img.win, 17, 1L << 17, ft_closebutton, scene);
	mlx_hook(img.win, 2, 1L << 0, ft_key, scene);
	mlx_mouse_hook(img.win, on_click, scene);
	mlx_loop(img.mlx);
}
