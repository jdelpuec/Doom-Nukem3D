/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:05:34 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/03/06 12:04:40 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"
#include "event.h"

int		check_seg_inter(t_ray *r, t_wall wall, float *h_x, float *h_y)
{
	int denom_is_pos;

	r->s10_x = wall.p2.x - wall.p1.x;
	r->s10_y = wall.p2.y - wall.p1.y;
	r->s32_x = r->ray_end.x - r->player.position.x;
	r->s32_y = r->ray_end.y - r->player.position.y;
	r->denom = r->s10_x * r->s32_y - r->s32_x * r->s10_y;
	if (r->denom == 0.0)
		return (0);
	denom_is_pos = r->denom > 0;
	r->s02_x = wall.p1.x - r->player.position.x;
	r->s02_y = wall.p1.y - r->player.position.y;
	r->s_denom = r->s10_x * r->s02_y - r->s02_x * r->s10_y;
	if ((r->s_denom < 0) == denom_is_pos)
		return (0);
	r->t_denom = r->s32_x * r->s02_y - r->s32_y * r->s02_x;
	if ((r->t_denom < 0) == denom_is_pos)
		return (0);
	if (((r->s_denom > r->denom) == denom_is_pos)
		|| ((r->t_denom > r->denom) == denom_is_pos))
		return (0);
	r->t = r->t_denom / r->denom;
	*h_x = wall.p1.x + (r->t * r->s10_x);
	*h_y = wall.p1.y + (r->t * r->s10_y);
	return (1);
}

int		sector_loop(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	int ret;

	ret = draw_wall(w, r, sector, wall);
	if (ret == 1)
		return (1);
	else if (ret == 2)
	{
		r->last_sec = r->old_wall.portal_sector;
		r->cur_sector = wall.portal_sector;
		r->old_wall = wall;
		return (0);
	}
	r->i++;
	return (2);
}

int		draw_sector(t_win *w, t_ray *r)
{
	t_sector	sector;
	t_wall		wall;
	int			ret;

	sector = r->sectors[r->cur_sector];
	r->light = sector.brightness;
	r->i = 0;
	while (r->i < sector.wall_count)
	{
		wall = sector.walls[r->i];
		if (wall.portal_sector != -1)
			if (wall.portal_sector == r->player.sector
				|| wall.portal_sector == r->last_sec)
			{
				if (wall.portal_sector == r->player.sector)
					r->last_sec = -2;
				r->i++;
				continue;
			}
		ret = sector_loop(w, r, sector, wall);
		if (ret == 0 || ret == 1)
			return (ret);
	}
	return (0);
}

void	draw_player_view(t_win *w, t_ray *r)
{
	int			iter;
	int			running;

	r->x = 0;
	r->ray_angle = (deg_to_rad(-30.0) + r->player.angle);
	while (r->x < WIN_W)
	{
		r->last_sec = -2;
		r->ray_end.x = r->player.position.x + cosf(r->ray_angle) * 200.0;
		r->ray_end.y = r->player.position.y - sinf(r->ray_angle) * 200.0;
		r->cur_sector = r->player.sector;
		iter = 0;
		running = 0;
		while (running == 0)
		{
			iter++;
			if (iter >= SECTOR_ITER_MAX)
				break ;
			running = draw_sector(w, r);
		}
		r->ray_angle += deg_to_rad(60.0) / WIN_W;
		r->x++;
	}
}

void	drawing(t_win *w, t_ray *r, t_keyboard *k)
{
	SDL_memset(w->surface->pixels, 0, ((WIN_W * WIN_H) << 2));
	if (w->e.type == SDL_KEYUP)
		w->eat = 0;
	draw_player_view(w, r);
	if (r->inv.nb_sprites > 0)
		raysprite(w, r);
	hud(w, r);
	r->inv.nb_sprites > 0 ? inventory(r, w) : 0;
	if (k->state[SDL_SCANCODE_O] == 1)
		print_messages(w);
	w->fired == 0 ? display_l((WIN_W / 2), (WIN_H) - 240, w, r->gun) : 0;
	if (w->fired == 1)
		fire_gunshot(w, &r->gun);
	if (w->reload == 1)
		reload_gun(&r->reload_gun, w);
	if (r->inv.nb_hp == 100 && w->youwin == 0)
	{
		w->youwin = 1;
		FMOD_System_PlaySound(w->s.fmod, FMOD_CHANNEL_FREE, w->s.win, 0, NULL);
	}
	SDL_UpdateWindowSurface(w->win);
}
