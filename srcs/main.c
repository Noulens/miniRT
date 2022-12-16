/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:12:29 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/16 16:37:29 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

# define KEY_ESC	65307

typedef struct s_data{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_w;
	int		win_h;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
		char	*dst;

		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel )/ 8);
		*(unsigned int*)dst = color;
}

int	close_window(t_data *img)
{
	mlx_destroy_window(img->mlx_ptr, img->mlx_win);
	mlx_loop_end(img->mlx_ptr);
	mlx_destroy_image(img->mlx_ptr, img->img);
	mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *img)
{
	if (keycode == KEY_ESC)
		close_window(img);
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_data	img;


	img.win_w = 256;
	img.win_h = 256;
	img.mlx_ptr = mlx_init();
	if (!img.mlx_ptr)
		return (0);
	img.mlx_win= mlx_new_window(img.mlx_ptr, img.win_w , img.win_h, "Mini RT");
	if (!img.mlx_ptr)
		return (0);
	img.img = mlx_new_image(img.mlx_ptr, img.win_w , img.win_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(img.mlx_ptr, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 1L << 0, &key_press, &img);
	mlx_hook(img.mlx_win, 17, 1L << 0, &close_window, &img);
	mlx_loop(img.mlx_ptr);
}
