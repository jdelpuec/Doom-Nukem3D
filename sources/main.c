/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by ebonafi           #+#    #+#             */
/*   Updated: 2020/01/06 18:08:26 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "define.h"
#include "raycasting.h"
#include "event.h"


void	init_sdl(t_win *w)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("\n\n");
	}
	w->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (!w->win)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("\n\n");
	}
	if ((w->surface = SDL_GetWindowSurface(w->win)) == NULL)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("Surface error.\n");
	}
	// SDL_ShowCursor(0);
}

void	init_t_ray(t_ray *r)
{
	r->dist_pp = WIN_W / tanf(deg_to_rad(30.0));
}

int		check_seg_intersection(t_ray *r, t_wall wall, float *h_x, float *h_y)
{
	int	denom_is_pos;

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
	
	if (((r->s_denom > r->denom) == denom_is_pos) || ((r->t_denom > r->denom) == denom_is_pos))
		return (0);
	
	r->t = r->t_denom / r->denom;
	*h_x = wall.p1.x + (r->t * r->s10_x);
	*h_y = wall.p1.y + (r->t * r->s10_y);

	return (1);
}

int		draw_wall(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	int			i;
	float		hit_x;
	float		hit_y;
	t_sector	portal_sec;

	if (check_seg_intersection(r, wall, &hit_x, &hit_y) == 1)
	{
		if (wall.portal_sector >= 0)
		{
			portal_sec = r->sectors[wall.portal_sector];

			if (portal_sec.floor_height > sector.floor_height)
			{
				r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
				r->dist *= cos(r->ray_angle - r->player.angle);
				r->dist_wall = r->dist * 32.0;

				r->offset_start = (WIN_H / 2) + ((r->player.position.z - portal_sec.floor_height) / r->dist_wall) * r->dist_pp;
				r->offset_end = (WIN_H / 2) + ((r->player.position.z - sector.floor_height) / r->dist_wall) * r->dist_pp;

				printf("%f / %f \n", r->offset_start, r->offset_end);
				
				r->y_max = r->offset_start;
				i = (int)r->offset_start;
				while (i != (int)r->offset_end)
				{
					if (i >= 0 && i < WIN_H)
						*((int *)w->surface->pixels + (r->x * WIN_H + i)) = 0xffffff;
					i++;
				}
			}

			if (portal_sec.ceil_height < sector.ceil_height)
			{
				r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
				r->dist *= cos(r->ray_angle - r->player.angle);
				r->dist_wall = r->dist * 32.0;

				r->offset_start = (WIN_H / 2) + ((r->player.position.z - sector.ceil_height) / r->dist_wall) * r->dist_pp;
				r->offset_end = (WIN_H / 2) + ((r->player.position.z - portal_sec.ceil_height) / r->dist_wall) * r->dist_pp;
				
				printf("%f / %f \n", r->offset_start, r->offset_end);
				
				r->y_min = r->offset_end;
				i = (int)r->offset_start;
				while(i != (int)r->offset_end)
				{
					if (i >= 0 && i < WIN_H)
						*((int *)w->surface->pixels + (r->x * WIN_H + i)) = 0xffffff;
					i++;
				}
			}
			return (2);
		}
		else
		{
			r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
			r->dist *= cos(r->ray_angle - r->player.angle);
			r->dist_wall = r->dist * 32.0;

			r->line_h = ((sector.ceil_height - sector.floor_height) / r->dist_wall) * r->dist_pp;
			r->offset_start = (WIN_H / 2) + ((r->player.position.z - sector.ceil_height) / r->dist_wall) * r->dist_pp;
			r->offset_end = (WIN_H / 2) + ((r->player.position.z - sector.floor_height) / r->dist_wall) * r->dist_pp;

			printf("%f / %f \n", r->offset_start, r->offset_end);

			i = (int)r->offset_start;
			while(i != (int)r->offset_end)
			{
				ft_putendl("ok");
				if (i >= 0 && i < WIN_H)
					if (i> r->y_min && i < r->y_max)
						*((int *)w->surface->pixels + (r->x * WIN_H + i)) = 0xffffff;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

int		draw_sector(t_win *w, t_ray *r)
{
	t_sector	sector;
	t_wall		wall;
	int			i;
	int			ret;

	sector = r->sectors[r->cur_sector];
	i = 0;
	while (i != sector.wall_count)
	{
		wall = sector.walls[i];
		if (r->old_wall.p1.x == wall.p1.x && r->old_wall.p1.y == wall.p1.y 
			&& r->old_wall.p2.x == wall.p2.x && r->old_wall.p2.y == wall.p2.y)
			continue;
		ret = draw_wall(w, r, sector, wall);
		if (ret == 1)
			return (1);
		else if (ret == 2)
		{
			r->cur_sector = wall.portal_sector;
			r->old_wall = wall;
			return (0);
		}
		i++;
	}
	return (0);
}

void	draw_player_view(t_win *w, t_ray *r)
{
	int			iter;
	int			running;

	iter	= 0;
	running	= 0;
	r->ray_angle = (deg_to_rad(-30.0) + r->player.angle);
	while (r->x < WIN_W)
	{
		r->ray_end.x = r->player.position.x + cosf(r->ray_angle) * 200.0;
		r->ray_end.y = r->player.position.y + sinf(r->ray_angle) * 200.0;
		r->cur_sector = r->player.sector;
		if (running == 0)
		{
			iter++;
			if (iter >= SECTOR_ITER_MAX)
			{
				ft_putendl("Sector_iter_max reached");
				break ;
			}
			else
				running = draw_sector(w, r);
		}
		r->ray_angle += deg_to_rad(60.0) / WIN_W;
		r->x++;
	}
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
		if (is_key_pressed(&k) > 0)
		{
			handle_keyboard_mvt(w, r, &k);
		}
		draw_player_view(w, r);
		SDL_UpdateWindowSurface(w->win);
		ft_bzero(w->surface->pixels, WIN_W*WIN_H*4);
	}
}

int		main(void)
{
	t_ray	r;
	t_win	w;

	init_t_ray(&r);
	init_sdl(&w);
	r.sectors = map();
	sdl_loop(&w, &r);
	return (0);
}
