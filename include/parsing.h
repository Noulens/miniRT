/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:58:19 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/23 12:43:59 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "colors.h"
# include "math_func.h"
# include "tools.h"

#ifndef BONUS
# define BONUS 0
#endif

typedef struct s_plan
{
	t_vec3	pos;
	t_vec3	orientation;
	t_vec3	translate;
	t_vec3	rotate;
	int 	color;
}	t_pl;

typedef struct s_cy
{
	t_vec3	pos;
	t_vec3	orientation;
	t_vec3	translate;
	t_vec3	rotate;
	int 	color;
	float 	height;
	float 	diameter;
}	t_cy;

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
	t_light		light;
	t_alight	alight;
	t_stdobj	*objects;
	t_cam		cam;
	int			bg_color;
}	t_scene;

int		rt_name_checker(char *path);
int		parse(t_scene *scn, char *str);
int		get_infos_a(char *line, t_scene *scn);
int		get_infos_c(char *line, t_scene *scn);
int		get_infos_l(char *line, t_scene *scn);
void	init_iter(int *i, int *commas);
void	inc_iter(int *i, int *commas);
void	skip_spaces(int *i, char *line);
int		check_decimal(int *i, char *line);
int		check_int_part(int *i, int *commas, char *line);
int		check_fformat(int *i, int *commas, char *line);
int		check_float_nb(int *i, char *line);
int		check_rgb(char *str);
int		atorgb(char *line);
int		count_element(char *line);
int		get_floats(char *line, t_vec3 *vector, char mode);
int 	parse_pl(char *line, t_scene *scn);
int 	parse_cy(char *line, t_scene *scn);
int 	parse_sp(char *line, t_scene *scn);
int 	parse_hy(char *line, t_scene *scn);
int 	parse_co(char *line, t_scene *scn);
int		parse_cy_2(char *line, t_cy *cylinder, int *j, t_scene *scn);


#endif
