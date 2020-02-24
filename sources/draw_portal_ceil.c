/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_portal_ceil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:13:16 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/19 16:16:32 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void	draw_portal_ceil(t_win *w, t_ray *r, t_sector sector,
															t_sector portal_sec)
{
	int i;

	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAY_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
				- sector.ceil_height) / r->dist_wall) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
				- portal_sec.ceil_height) / r->dist_wall) * r->dist_pp;
	i = -1;
	while (++i < (int)r->offset_start)
		if ((i >= 0 && i < WIN_H) && (i >= r->y_min && i < r->y_max - 1)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = GREY;
	while (i++ < (int)r->offset_end)
		if ((i >= 0 && i < WIN_H) && (i >= r->y_min && i < r->y_max - 1)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = RED * r->light;
	r->y_min = (int)r->offset_end;
}
