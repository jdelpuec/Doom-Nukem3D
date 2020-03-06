/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal_ceil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:13:16 by lubernar          #+#    #+#             */
/*   Updated: 2020/03/06 13:02:04 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"

void	draw_portal_ceil(t_win *w, t_ray *r, t_sector sector,
															t_sector portal_sec)
{
	int			i;
	t_wall_tex	wt;
	t_text_tab	tmp;

	tmp = w->text_list;
	while (sector.id_ceil != tmp.id)
		tmp = *tmp.next;
	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAY_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
				- sector.ceil_height) / r->dist_wall) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
				- portal_sec.ceil_height) / r->dist_wall) * r->dist_pp;
	r->line_h = r->offset_end - r->offset_start;
	i = -1;
	while (++i <= (int)r->offset_start)
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = r->light
				== 1.0 ? GREY : add_light(r, GREY);
	wt = set_wall_tex(w, r, sector, sector.walls[r->i]);
	display_text(r, w, &tmp, &wt);
}
