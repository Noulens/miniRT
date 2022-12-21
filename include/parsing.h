/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:58:19 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 17:17:40 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "colors.h"
# include "math_func.h"

# define FAIL 1
# define SUCCESS 0

typedef enum e_obj
{
	SP,
	CY,
	PL
}	t_objtp;

typedef struct s_object // TODO : a refaire pour généraliser le type d'objet
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
	t_objtp	objtp;
}	t_object;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	t_vec3	orientation;
	int		fov_w;
	int		fov_h;
	float	fov_h_len;
	float	focal_length;
}	t_cam;

typedef struct s_light
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
	float	brightness;
}	t_light;

typedef struct s_alight
{
	float	al;
	int		color;
}	t_alight;

typedef struct s_scene
{
	int			win_w;
	int			win_h;
	float		image_ratio;
	int			num_objects_in_scene;
	t_light		*light;
	t_alight	*alight;
	t_object	*objects;
	t_cam		cam;
	int			bg_color;
}	t_scene;

int rt_name_checker(char *path);
int parse(t_scene *scn, char *str);
int get_infos_a(char *line, t_scene scn);
int get_infos_c(char *line, t_scene scn);
int get_infos_l(char *line, t_scene scn);

#endif
