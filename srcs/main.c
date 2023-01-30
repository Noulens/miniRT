/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:12:29 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/23 17:18:19 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scn;

	if (scenevarinit(&scn), argc == 2 && rt_name_checker(argv[1])
		&& !parse(&scn, argv[1]))
	{
		win_launcher(&scn);
	}
	else
	{
		ft_fprintf(2, "Error\nUsage : ./miniRT <filename.rt>\n");
		des_minirt(&scn);
		return (1);
	}
	return (0);
}
