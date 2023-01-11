/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:21:14 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/23 16:49:59 by hyunah           ###   ########.fr       */
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

# include "init.h"
# include "destroy.h"
# include "render.h"

int		ft_closebutton(void *param);
int		ft_key(int key, void *img);
int		on_click(int code, int x, int y, void *param);
void	ft_rotation_x(void *obj);
void	ft_rotation_y(void *obj);
void	ft_rotation_z(void *obj);

#endif
