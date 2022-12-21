/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:18:53 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/21 15:01:07 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "mlx.h"
# include "libft.h"
# include "colors.h"
# include "tools.h"
# include "math_func.h"
# include "interaction.h"

typedef struct s_object // TODO : a refaire pour généraliser le type d'objet
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
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

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_scene	*scene;
}	t_img;

t_scene scene_init(t_scene *s);

#endif
