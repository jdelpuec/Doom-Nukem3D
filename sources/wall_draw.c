/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:12:36 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/03/06 11:06:32 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"

void	draw_portal_floor(t_win *w, t_ray *r, t_sector sector,
															t_sector portal_sec)
{
	int			i;
	t_wall_tex	wt;
	t_text_tab	tmp;

	tmp = w->text_list;
	while (sector.id_floor != tmp.id)
		tmp = *tmp.next;
	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAY_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
				- portal_sec.floor_height) / r->dist_wall) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
				- sector.floor_height) / r->dist_wall) * r->dist_pp;
	r->line_h = r->offset_end - r->offset_start;
	wt = set_wall_tex(w, r, sector, sector.walls[r->i]);
	i = display_text(r, w, &tmp, &wt) - 1;
	while (i++ < WIN_H - 1)
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = r->light
				== 1.0 ? DARK : add_light(r, DARK);
}

int		draw_portal(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	t_sector portal_sec;

	portal_sec = r->sectors[wall.portal_sector];
	draw_portal_ceil(w, r, sector, portal_sec);
	draw_portal_floor(w, r, sector, portal_sec);
	return (2);
}

int		draw_wall_2(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAY_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
				- sector.ceil_height) / r->dist_wall) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
				- sector.floor_height) / r->dist_wall) * r->dist_pp;
	r->line_h = r->offset_end - r->offset_start;
	wall_textures(w, r, sector, wall);
	return (1);
}

int		check_behind(t_ray *r, t_sector sector)
{
	int			i;
	t_vector_2d	tmp;

	if (r->sector_count > 1)
		return (1);
	i = 0;
	while (i < sector.wall_count)
	{
		if (i != r->i && (check_seg_inter(r, sector.walls[i],
														&tmp.x, &tmp.y) == 1))
		{
			if (fabsf(tmp.x - r->player.position.x)
				< fabsf(r->hit_x - r->player.position.x)
				&& fabsf(tmp.y - r->player.position.y)
					< fabsf(r->hit_y - r->player.position.y))
				return (-1);
		}
		i++;
	}
	return (1);
}

int		draw_wall(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	if (check_seg_inter(r, wall, &r->hit_x, &r->hit_y) == 1
		&& (check_behind(r, sector) == 1))
	{
		if (wall.portal_sector != -1)
			return (draw_portal(w, r, sector, wall));
		else
			return (draw_wall_2(w, r, sector, wall));
	}
	return (0);
}
