/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/15 19:22:56 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "destroy.h"

int	rt_name_checker(char *path)
{
	int	i;
	int	fd;
	int	map;

	map = 1;
	if (path == NULL)
		map = 0;
	i = ft_strlen(path);
	if (i <= 3)
		map = 0;
	if (!ft_strnstr(path + i - 3, ".rt", 3))
		map = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		map = 0;
	else
		close(fd);
	if (!map)
		ft_fprintf(2, RED"Usage : ./miniRT <filename.rt>\n"RESET);
	return (map);
}

void	win_launcher(void)
{
	void	*mlx;
	void	*win;
	t_img	img;

	mlx = mlx_init();
	if (!mlx)
		exit(EXIT_FAILURE);
	win = mlx_new_window(mlx, 600, 300, "miniRT");
	img.img = mlx_new_image(mlx, 600, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
//		mlx_key_hook(win, ft_key, NULL);
//		mlx_hook(win, 17, 1L << 17, ft_closebutton, NULL);
//		mlx_hook(win, 2, 1L << 0, ft_escape, NULL);
	mlx_loop(mlx);
	des_mlx(mlx, img.img, win);
}
