/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/12 17:48:06 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "doom.h"
#include "raycasting.h"
#include "draw.h"
#include "init.h"
#include "event.h"

// void	init_sdl(t_win *w)
// {
// 	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
// 	{
// 		ft_putstr(SDL_GetError());
// 		ft_putstr("\n\n");
// 	}
// 	w->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
// 	if (!w->win)
// 	{
// 		ft_putstr(SDL_GetError());
// 		ft_putstr("\n\n");
// 	}
// 	if ((w->surface = SDL_GetWindowSurface(w->win)) == NULL)
// 	{
// 		ft_putstr(SDL_GetError());
// 		ft_putstr("Surface error.\n");
// 	}
// 	SDL_ShowCursor(0);
// }

// void	init_t_ray(t_ray *r)
// {
// 	r->dist_pp	= WIN_W / tanf(deg_to_rad(30.0));
// 	r->last_sec = -2;
// 	r->speed	= 5.0;
// 	r->thresh	= 1;
// }

// int		check_seg_intersection(t_ray *r, t_wall wall, float *h_x, float *h_y)
// {
// 	int	denom_is_pos;

// 	r->s10_x = wall.p2.x - wall.p1.x;
// 	r->s10_y = wall.p2.y - wall.p1.y;
// 	r->s32_x = r->ray_end.x - r->player.position.x;
// 	r->s32_y = r->ray_end.y - r->player.position.y;
// 	r->denom = r->s10_x * r->s32_y - r->s32_x * r->s10_y;

// 	if (r->denom == 0.0)
// 		return (0);

// 	denom_is_pos = r->denom > 0;
// 	r->s02_x = wall.p1.x - r->player.position.x;
// 	r->s02_y = wall.p1.y - r->player.position.y;
// 	r->s_denom = r->s10_x * r->s02_y - r->s02_x * r->s10_y;

// 	if ((r->s_denom < 0) == denom_is_pos)
// 		return (0);

// 	r->t_denom = r->s32_x * r->s02_y - r->s32_y * r->s02_x;

// 	if ((r->t_denom < 0) == denom_is_pos)
// 		return (0);

// 	if (((r->s_denom > r->denom) == denom_is_pos) || ((r->t_denom > r->denom) == denom_is_pos))
// 		return (0);

// 	r->t = r->t_denom / r->denom;
// 	*h_x = wall.p1.x + (r->t * r->s10_x);
// 	*h_y = wall.p1.y + (r->t * r->s10_y);

// 	return (1);
// }

// int		draw_wall(t_win *w, t_ray *r, t_sector sector, t_wall wall)
// {
// 	int			i;
// 	float		hit_x;
// 	float		hit_y;
// 	t_sector	portal_sec;

// 	if (check_seg_intersection(r, wall, &hit_x, &hit_y) == 1)
// 	{
// 		if (wall.portal_sector >= 0)
// 		{
// 			portal_sec = r->sectors[wall.portal_sector];
// 			if (portal_sec.floor_height > sector.floor_height)
// 			{
// 				r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
// 				r->dist *= cos(r->ray_angle - r->player.angle);
// 				r->dist_wall = r->dist * 32.0;

// 				r->offset_start = (WIN_H >> 1) + ((r->player.position.z - portal_sec.floor_height) / r->dist_wall) * r->dist_pp;
// 				r->offset_end = (WIN_H >> 1) + ((r->player.position.z - sector.floor_height) / r->dist_wall) * r->dist_pp;

// 				i = (int)r->offset_start;

// 				i++;
// 				while (i < (int)r->offset_end)
// 				{
// 					if (i >= 0 && i < WIN_H)
// 						if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 							*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0x0000ff * r->light;		// Next sector floor diff
// 					i++;
// 				}
// 				i++;
// 				while (i < WIN_H)
// 				{
// 					if (i >= 0 && i < WIN_H)
// 						if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 							*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0x303030 * r->light;	// Next sector ground
// 					i++;
// 				}
// 				r->y_max = (int)r->offset_start;
// 			}

// 			if (portal_sec.ceil_height < sector.ceil_height)
// 			{
// 				r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
// 				r->dist *= cos(r->ray_angle - r->player.angle);
// 				r->dist_wall = r->dist * 32.0;

// 				r->offset_start = (WIN_H >> 1) + ((r->player.position.z - sector.ceil_height) / r->dist_wall) * r->dist_pp;
// 				r->offset_end = (WIN_H >> 1) + ((r->player.position.z - portal_sec.ceil_height) / r->dist_wall) * r->dist_pp;

// 				// i = (int)r->offset_start;

// 				//
// 				i = 0;

// 				while (i < (int)r->offset_start)
// 				{
// 					if (i >= 0 && i < WIN_H)
// 						if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 							*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0x808080 * r->light;
// 					i++;
// 				}
// 				i++;
// 				//
// 				while(i < (int)r->offset_end)
// 				{
// 					if (i >= 0 && i < WIN_H)
// 						if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 							*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0xff0000 * r->light;	// NExt sector ceil diff
// 					i++;
// 				}
// 				r->y_min = (int)r->offset_end;
// 			}
// 			return (2);
// 		}
// 		else
// 		{
// 			r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
// 			r->dist *= cos(r->ray_angle - r->player.angle);
// 			r->dist_wall = r->dist * 32.0;

// 			r->offset_start = (WIN_H >> 1) + ((r->player.position.z - sector.ceil_height) / r->dist_wall) * r->dist_pp;
// 			r->offset_end = (WIN_H >> 1) + ((r->player.position.z - sector.floor_height) / r->dist_wall) * r->dist_pp;

// 			i = 0;
// 			while (i < (int)r->offset_start)
// 			{
// 				if (i >= 0 && i < WIN_H)
// 					if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 						*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0x808080 * r->light;
// 				i++;
// 			}
// 			///
// 			i++;
// 			while(i < (int)r->offset_end)
// 			{
// 				if (i >= 0 && i < WIN_H)
// 					if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 						*((int *)w->surface->pixels + (i * WIN_W + r->x)) = (r->cur_sector + 1) * 25000 * r->light;
// 				i++;
// 			}

// 			///
// 			i++;
// 			while (i < WIN_H)
// 			{
// 				if (i >= 0 && i < WIN_H)
// 					if (i > r->y_min && i < r->y_max && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
// 						*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0x303030 * r->light;
// 				i++;
// 			}
// 			// /
// 			// r->y_min = (int)r->offset_end;
// 			// r->y_max = (int)r->offset_start;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int		draw_sector(t_win *w, t_ray *r)
// {
// 	t_sector	sector;
// 	t_wall		wall;
// 	int			i;
// 	int			ret;

// 	sector		= r->sectors[r->cur_sector];
// 	r->light	= sector.brightness;
// 	i = 0;
// 	while (i < sector.wall_count)
// 	{
// 		wall = sector.walls[i];
// 		if (wall.portal_sector != -1)
// 			if (wall.portal_sector == r->player.sector || wall.portal_sector == r->last_sec)
// 			{
// 				if (wall.portal_sector == r->player.sector)
// 					r->last_sec = -2;
// 				i++;
// 				continue;
// 			}
// 		ret = draw_wall(w, r, sector, wall);
// 		if (ret == 1)
// 			return (1);
// 		else if (ret == 2)
// 		{
// 			r->last_sec = r->old_wall.portal_sector;
// 			r->cur_sector = wall.portal_sector;
// 			r->old_wall = wall;
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	draw_player_view(t_win *w, t_ray *r)
// {
// 	int			iter;
// 	int			running;

// 	r->x = 0;
// 	r->ray_angle = (deg_to_rad(-30.0) + r->player.angle);
// 	while (r->x < WIN_W)
// 	{
// 		r->last_sec = -2;
// 		r->ray_end.x = r->player.position.x + cosf(r->ray_angle) * 200.0;
// 		r->ray_end.y = r->player.position.y - sinf(r->ray_angle) * 200.0;
// 		r->cur_sector = r->player.sector;
// 		r->y_min	= 0;
// 		r->y_max	= WIN_H - 1;
// 		iter	= 0;
// 		running	= 0;
// 		while (running == 0)
// 		{
// 			iter++;
// 			if (iter >= SECTOR_ITER_MAX)
// 				break ;
// 			running = draw_sector(w, r);
// 		}
// 		r->ray_angle += deg_to_rad(60.0) / WIN_W;
// 		r->x++;
// 	}
// }

// void	drawing(t_win *w, t_ray *r)
// {
// 	r->inv.sprite.x = 0;
// 	r->inv.sprite.y = 5;
// 	r->inv.sprite.num_sprite = 1;
// 	r->inv.sprite.pickable = 1;
// 	if (w->fps > 50)
// 	{
// 		SDL_memset(w->surface->pixels, 0, ((WIN_W * WIN_H) << 2));
// 		draw_player_view(w, r);
// 	}
// 	init_gun(w, &r->gun);
// 	inventory(r, w, &r->inv);
// 	// draw_minimap(w, r);	//A finir .... voir abandonner si optionnel

// 	// --> mettre ici les sprites :

// 	//

// 	// --> mettre ici l'affichage de l'HUD :

// 	//
// 	SDL_UpdateWindowSurface(w->win);
// }

void	fps_count(t_win *w)
{
	float	delta;

	w->old_time	= w->time;
	w->time		= SDL_GetTicks();
	delta		= (w->time - w->old_time) / 1000.0;
	w->fps		= (int)(1.0 / delta);
}

void	sdl_loop(t_win *w, t_ray *r)
{
	t_keyboard k;
	
	init_keyboard(&k);
	while (1)
	{
		while (SDL_PollEvent(&w->e))
		{
			if (w->e.type == SDL_KEYDOWN || w->e.type == SDL_KEYUP)
				if (handle_keyboard_event(w, &k) < 0)
					return ;
			if (w->e.type == SDL_MOUSEMOTION)
				handle_mouse_event(w, r);
		}
		if (is_key_pressed(&k) > 0 || r->player.position.z
			!= r->sectors[r->cur_sector].floor_height + 32)
			handle_keyboard_mvt(w, r, &k);
		drawing(w, r);
		fps_count(w);
	}
}

int		main(void)
{
	t_ray	r;
	t_win	w;

	r.sectors = map();
	init_t_ray(&r);

	r.sector_count = 12;		// Brut map ---> need to implemant parsing
	r.player.sector = 0;
	r.player.position.z = 0 + PLAYER_H;
	w.pressed = 0;
	init_sdl(&w);
	w.old_time	= 0.0;
	w.time		= 0.0;
	w.old_t		= 0.0;

	w.text_list = init_text();


	init_sdl(&w);
	sdl_loop(&w, &r);
	return (0);
}
