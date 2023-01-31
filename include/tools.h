/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:44:04 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/31 11:17:01 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define FAIL 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# include <math.h>
# include "libft.h"
# include "struct.h"

int		ft_trgb(int t, int r, int g, int b);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		float_range_checker(float val, float lower, float upper, int incl);
int		rgb_range_checker(char *line);
int		objadd_front(t_stdobj **lst, void *new, t_objtp type, int color);
void	objclear(t_stdobj *lst);
int		objlstsize(t_stdobj *lst);
int		list_to_tab(t_scene *scn);
void	ft_swap(float *a, float *b);
int		objadd_front_l(t_light **lst);
void	lpdes_l(t_light *lst);
int		objlstsize_l(t_light *lst);
int		list_to_tab_l(t_scene *scn);
void	keep_between_zero_one(float *f);

#endif
