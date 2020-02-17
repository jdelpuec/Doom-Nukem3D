/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:08:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/13 15:26:16 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "event.h"

void	drawing(t_win *w, t_ray *r, t_keyboard *k);
void	draw_player_view(t_win *w, t_ray *r);
int		draw_sector(t_win *w, t_ray *r);
int		sector_loop(t_win *w, t_ray *r, t_sector sector, t_wall wall);
int		draw_wall(t_win *w, t_ray *r, t_sector sector, t_wall wall);

int		check_seg_intersection(t_ray *r, t_wall wall, float *h_x, float *h_y);

float		check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p);

void		init_raycasting(t_ray *r);
#endif