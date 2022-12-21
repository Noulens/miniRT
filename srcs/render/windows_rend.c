/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_rend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:32:44 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 13:32:59 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void win_launcher(void)
{
    t_scene scene;
    t_img img;

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
