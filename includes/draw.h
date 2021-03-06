/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:08:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/03/06 13:01:55 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "event.h"

void		drawing(t_win *w, t_ray *r, t_keyboard *k);
void		draw_player_view(t_win *w, t_ray *r);
int			draw_sector(t_win *w, t_ray *r);
int			sector_loop(t_win *w, t_ray *r, t_sector sector, t_wall wall);
int			draw_wall(t_win *w, t_ray *r, t_sector sector, t_wall wall);
void		draw_portal_ceil(t_win *w, t_ray *r, t_sector sector,
														t_sector portal_sec);
int			add_light(t_ray *ray, int color);
t_wall_tex	set_wall_tex(t_win *w, t_ray *r, t_sector sector, t_wall wall);
int			display_text(t_ray *r, t_win *w, t_text_tab *tmp, t_wall_tex *wt);
int			check_frontground(t_ray *r);
int			check_spr_inter(t_ray *r, t_sprites sprite, float *h_x, float *h_y);
int			sprite_close(t_vector_3d player, t_vector_3d sprite);
int			detecte_sprite(t_win *w, t_ray *r);
int			draw_sprite(t_win *w, t_ray *r);
void		display_spr_2(t_ray *r, t_win *w, t_text_tab sprt, t_wall_tex *st);
int			check_seg_inter(t_ray *r, t_wall wall, float *h_x, float *h_y);
float		check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p);
void		init_raycasting(t_ray *r);
#endif
