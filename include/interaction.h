/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:21:14 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/26 09:32:35 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTION_H
# define INTERACTION_H
# define KEY_ESC 65307
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define KEY_SPACE 32
# define KEY_CTRL 65507
# define KEY_C 99
# define KEY_L 108
# define NUMPAD_0 65438
# define NUMPAD_1 65436
# define NUMPAD_2 65433
# define NUMPAD_3 65435
# define NUMPAD_4 65430
# define NUMPAD_5 65437 
# define NUMPAD_6 65432
# define NUMPAD_7 65429
# define NUMPAD_8 65431
# define NUMPAD_9 65434

# include "init.h"
# include "destroy.h"
# include "render.h"

int		ft_closebutton(void *param);
int		ft_key(int key, void *img);
int		on_click(int code, int x, int y, void *param);
void	ft_rotation_x(void *obj);
void	ft_rotation_y(void *obj);
void	ft_rotation_z(void *obj);
int		modify_objects(void *param, int key);
void	do_orientation(int key, t_vec3 *orientation);
void	do_transform_s(t_sp *sp, int key);
void	do_transform_c(t_cy *cy, int key);
void	do_transform_p(t_pl *pl, int key);
int		is_keycam(int key);
int		is_objkey(int key);
void	adjust_cone(t_stdobj *obj, int key, t_scene *scene);
int		is_lightkey(int key);
int		move_light(void *param, int keycode);
void	put_debug_to_window(void *mlx, void *win, t_scene *scene);
char	*ft_ftoa(float a, int precision);
void	put_debug_to_window(void *mlx, void *win, t_scene *s);
char	*ft_ftoa(float a, int precision);
char	*vec_to_string(t_vec3 vec);
int		ft_mlx_inst_out(t_scene *s, char *param, char *inst[4], int a);
int		ft_mlx_vec_out(t_scene *s, int i, char *p, char *t[4]);
int		ft_mlx_float_out(t_scene *s, int i, char *p, char *t);
// int		ft_mlx_vec_out(t_scene *s, t_vec3 v, int i, int gap);
// int		ft_mlx_float_out(t_scene *s, float f, int i, int gap);

#endif
