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
# include "init.h"

# define PLAN_ORI "Error\nplan orientation\n"
# define ERCY "Error\nparse_cy: position\n"
# define ERC2 "Error\nparse_cy: orientation\n"
# define ERC3 "Error\nparse_cy: diameter\n"
# define ERCO "Error\nparse_co: position\n"
# define ERO2 "Error\nparse_co: orientation\n"
# define ERO3 "Error\nparse_co: diameter\n"
# define ERSPH1 "Error\nparse_sp: pos\n"
# define ERSPH2 "Error\nparse_sp: dia\n"
# define ERSPH3 "Error\nparse_sp: rgb\n"
# define ERSPH "Error\nparse_sp: add\n"
# define FFC "Error\nin C data: coordinates format\n"
# define FFL "Error\nin L data: coordinates format\n"
# define ER_NORM "Error\nin orientation: for normalization: length is 0\n"

int		rt_name_checker(char *path);
int		parse(t_scene *scn, char *str);
int		get_infos_a(char *line, t_scene *scn);
int		get_infos_c(char *line, t_scene *scn);
int		get_infos_l(char *line, t_scene *scn);
void	init_iter(int *i, int *commas);
void	inc_iter(int *i, int *commas);
int		check_decimal(int *i, char *line);
int		check_int_part(int *i, int *commas, char *line);
int		check_fformat(int *i, int *commas, char *line);
int		check_float_nb(char *line);
int		check_rgb(char *str);
int		atorgb(char *line);
int		count_element(char *line);
int		get_floats(char *line, t_vec3 *vector, char mode);
int		parse_pl(char *line, t_scene *scn);
int		parse_cy(char *line, t_scene *scn);
int		parse_sp(char *line, t_scene *scn);
int		parse_co(char *line, t_scene *scn);
int		parse_cy_2(char **line, t_cy *cylinder, t_scene *scn);
int		parse_co_2(char **ptr, t_co *cone, t_scene *scn);

#endif
