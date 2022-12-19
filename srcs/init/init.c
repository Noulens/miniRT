/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:22:52 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/19 12:38:52 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "interaction.h"
#include "scene.h"

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

t_scene *scene_init()
{
	t_scene	*s;

	s = malloc(sizeof(t_scene));
	if (!s)
		return (NULL);
	s->win_h = 500;
	s->win_w = 1000;
	s->bg_color = set_vec(255, 255, 255);
	return (s);
}

void	win_launcher(void)
{
	t_scene	*scene;
	t_img	img;

	img.mlx = mlx_init();
	if (!img.mlx)
		exit(EXIT_FAILURE);
	scene = scene_init();
	img.win = mlx_new_window(img.mlx, scene->win_w, scene->win_h, "miniRT");
	img.img = mlx_new_image(img.mlx, scene->win_w, scene->win_h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
			&img.endian);
	// mlx_key_hook(win, ft_key, &img);
	render(&img, scene);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_hook(img.win, 17, 1L << 17, ft_closebutton, &img);
	mlx_hook(img.win, 2, 1L << 0, ft_key, &img);
	mlx_loop(img.mlx);
}
