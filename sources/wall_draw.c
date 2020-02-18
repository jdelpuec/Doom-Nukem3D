/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:12:36 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/18 12:09:49 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"

void	draw_portal_ceil(t_win *w, t_ray *r, t_sector sector,
															t_sector portal_sec)
{
	int i;

	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAYER_H;
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
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = RED * r->light; // NExt sector ceil diff
	r->y_min = (int)r->offset_end;
}

void	draw_portal_floor(t_win *w, t_ray *r, t_sector sector,
															t_sector portal_sec)
{
	int i;

	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAYER_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
				- portal_sec.floor_height) / r->dist_wall) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
				- sector.floor_height) / r->dist_wall) * r->dist_pp;
	i = (int)r->offset_start;
	while (i++ < (int)r->offset_end)
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = BLUE * r->light;
	while (i++ < WIN_H - 1)
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = DARK;
	r->y_max = (int)r->offset_start;
}

int		draw_portal(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	t_sector portal_sec;

	portal_sec = r->sectors[wall.portal_sector];
	if (portal_sec.floor_height > sector.floor_height)
		draw_portal_floor(w, r, sector, portal_sec);
	if (portal_sec.ceil_height < sector.ceil_height)
		draw_portal_ceil(w, r, sector, portal_sec);
	return (2);
}

int		draw_wall_2(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
		- r->player.position.x)) + ((r->hit_y - r->player.position.y)
		* (r->hit_y - r->player.position.y)));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_wall = r->dist * PLAYER_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
				- sector.ceil_height) / r->dist_wall) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
				- sector.floor_height) / r->dist_wall) * r->dist_pp;
	r->line_h = r->offset_end - r->offset_start;
	wall_textures(w, r, sector, wall);
	// if (r->last_sec == -2)
	// {
	// 	r->last_y_min = (int)r->offset_start;
	// 	r->last_y_max = (int)r->offset_end;
	// }
	return (1);
}

int		check_behind(t_ray *r, t_sector sector)
{
	int			i;
	t_vector_2d	tmp;
	t_vector_2d	hit;

	if (r->sector_count > 1)
		return (1);
	hit.x = r->hit_x;
	hit.y = r->hit_y;
	i = 0;
	while (i < sector.wall_count)
	{
		if (i != r->i && (check_seg_intersection(r, sector.walls[i],
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
	if (check_seg_intersection(r, wall, &r->hit_x, &r->hit_y) == 1
		&& (check_behind(r, sector) == 1))
	{
		if (wall.portal_sector >= 0)
			return (draw_portal(w, r, sector, wall));
		else
			return (draw_wall_2(w, r, sector, wall));
	}
	return (0);
}
