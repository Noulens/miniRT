/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:21:14 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 08:11:50 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTION_H
# define INTERACTION_H
# define KEY_ESC 65307
# define KEY_A 97

int	ft_closebutton(void *param);
int	ft_key(int keycode, t_img *img);

#endif
