/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_rend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:32:44 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/23 17:15:58 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void win_launcher(t_scene *scene)
{
    t_img   img;

	scene->ig = &img;
    img.mlx = mlx_init();
    if (!img.mlx)
	{
		objclear(scene->objects);
		exit(EXIT_FAILURE);
	}
    scene_init(scene);
    img.win = mlx_new_window(img.mlx, scene->win_w, scene->win_h, "miniRT");
    img.img = mlx_new_image(img.mlx, scene->win_w, scene->win_h);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
                                 &img.endian);
    render(scene);
    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_hook(img.win, 17, 1L << 17, ft_closebutton, scene);
    mlx_hook(img.win, 2, 1L << 0, ft_key, scene);
    mlx_loop(img.mlx);
}
