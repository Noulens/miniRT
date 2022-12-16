/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:12:29 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/15 17:12:39 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error_image(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img);
    return (0);
}

void	data_init(t_data *img)
{
    img->win_w = WINDOW_WIDTH;
    img->win_h = WINDOW_HEIGHT;
}
void	mlx_functions(t_data *img)
{
    mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img, 0, 0);
//    mlx_hook_interaction(img);
    mlx_loop(img->mlx_ptr);
    mlx_destroy_image(img->mlx_ptr, img->img);
    mlx_destroy_window(img->mlx_ptr, img->win_ptr);
    mlx_loop_end(img->mlx_ptr);
}
int	main(int argc, char **argv)
{
    t_data  data;

    (void) argc;
    (void) argv;
    data_init(&data);
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (0);
    printf("a\n");
    data.win_ptr = mlx_new_window(data.mlx_ptr, data.win_w, data.win_h, "MiniRT");
    printf("b\n");
    if (!data.win_ptr)
        return (error_image(&data));
    printf("c\n");
    data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.linel, &data.endian);
    printf("d\n");
    mlx_functions(&data);
    printf("e\n");
    return (0);
}
