/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by ebonafi           #+#    #+#             */
/*   Updated: 2020/01/15 17:49:11 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "draw.h"
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
	r->dist_pp	= WIN_W / tanf(deg_to_rad(30.0));
}

void	draw_point(t_win *w, int x, int y, int c)
{
    if(x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		*((int *)w->surface->pixels + (y * WIN_W + x)) = c;
}

void	draw_line(t_win *w, t_ray *r)
{
	t_line	l;
	int		tmp;
	int		y_longer;

	y_longer = 0;
	l.x_delta = r->x_2 - r->x_1;
	l.y_delta = r->y_2 - r->y_1;
	if (abs(l.y_delta) > abs(l.x_delta))
	{
		tmp = l.x_delta;
		l.x_delta = l.y_delta;
		l.y_delta = tmp;
		y_longer = 1;
	}
	l.end_val = l.x_delta;
	if (l.x_delta < 0)
	{
		l.incr = -1;
		l.x_delta = -l.x_delta;
	}
	else
		l.incr = 1;

	if (l.x_delta == 0)
		l.decr = (double)l.y_delta;
	else
		l.decr = (double)l.x_delta / (double)l.y_delta;

	l.j = 0.0;
	l.i = 0;
	if (y_longer == 1)
		while (l.i != l.end_val)
		{
			draw_point(w, (r->x_1 + (int)l.j), (r->y_1 + l.i), 0xff0000);
			l.j += l.decr;
			l.i += l.incr;
		}
	else
		while (l.i != l.end_val)
		{
			draw_point(w, (r->x_1 + l.i), (r->y_1 + (int)l.j), 0xff0000);
			l.j += l.decr;
			l.i += l.incr;
		}
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

				r->offset_start = (WIN_H >> 1) + ((r->player.position.z - portal_sec.floor_height) / r->dist_wall) * r->dist_pp;
				r->offset_end = (WIN_H >> 1) + ((r->player.position.z - sector.floor_height) / r->dist_wall) * r->dist_pp;

				r->y_max = r->offset_start;
				i = (int)r->offset_start;
				while (i < (int)r->offset_end)
				{
					if (i >= 0 && i < WIN_H)
						*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0xffffff;
					i++;
				}
			}

			if (portal_sec.ceil_height < sector.ceil_height)
			{
				r->dist = sqrtf(((hit_x - r->player.position.x) * (hit_x - r->player.position.x)) + ((hit_y - r->player.position.y) * (hit_y - r->player.position.y)));
				r->dist *= cos(r->ray_angle - r->player.angle);
				r->dist_wall = r->dist * 32.0;

				r->offset_start = (WIN_H >> 1) + ((r->player.position.z - sector.ceil_height) / r->dist_wall) * r->dist_pp;
				r->offset_end = (WIN_H >> 1) + ((r->player.position.z - portal_sec.ceil_height) / r->dist_wall) * r->dist_pp;
				
				r->y_min = r->offset_end;
				i = (int)r->offset_start;
				while(i < (int)r->offset_end)
				{
					if (i >= 0 && i < WIN_H)
						*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0xffffff;
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
			r->offset_start = (WIN_H >> 1) + ((r->player.position.z - sector.ceil_height) / r->dist_wall) * r->dist_pp;
			r->offset_end = (WIN_H >> 1) + ((r->player.position.z - sector.floor_height) / r->dist_wall) * r->dist_pp;

			i = (int)r->offset_start;
			while(i < (int)r->offset_end)
			{
				if (i >= 0 && i < WIN_H)
					if (i> r->y_min && i < r->y_max)
						*((int *)w->surface->pixels + (i * WIN_W + r->x)) = 0xffffff;
				i++;
			}
			return (1);
		}
	}
	// printf("%f ; %f ; %d \n", r->offset_start, r->offset_end, r->player.sector);
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
	while (i < sector.wall_count)
	{
		wall = sector.walls[i];
		if ((r->old_wall.p1.x == wall.p1.x && r->old_wall.p1.y == wall.p1.y 
			&& r->old_wall.p2.x == wall.p2.x && r->old_wall.p2.y == wall.p2.y)
			|| (r->old_wall.p1.x == wall.p2.x && r->old_wall.p1.y == wall.p2.y))
			{
				i++;
				continue;
			}
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

	r->x = 0;
	r->ray_angle = (deg_to_rad(-30.0) + r->player.angle);
	r->y_min	= 0;
	r->y_max	= WIN_H - 1;
	while (r->x < WIN_W)
	{
		r->ray_end.x = r->player.position.x + cosf(r->ray_angle) * 200.0;
		r->ray_end.y = r->player.position.y + sinf(r->ray_angle) * 200.0;
		r->cur_sector = r->player.sector;
		iter	= 0;
		running	= 0;
		while (running == 0)
		{
			iter++;
			if (iter >= SECTOR_ITER_MAX)
			{
				// ft_putendl("Sector_iter_max reached");
				break ;
			}
			running = draw_sector(w, r);
		}
		r->ray_angle += deg_to_rad(60.0) / WIN_W;
		r->x++;
	}
}

void	draw_minimap(t_win *w, t_ray *r)
{
	int i;
	int j;

	draw_point(w, (10 + ((int)r->player.position.x << 2)), (10 + ((int)r->player.position.y << 2)), 0x00ff00);
	i = 0;
	while (i < r->sector_count)
	{
		j = 0;
		while (j < r->sectors[i].wall_count)
		{
			r->x_1 = 10 + ((int)r->sectors[i].walls[j].p1.x << 2);
			r->y_1 = 10 + ((int)r->sectors[i].walls[j].p1.y << 2);
			r->x_2 = 10 + ((int)r->sectors[i].walls[j].p2.x << 2);
			r->y_2 = 10 + ((int)r->sectors[i].walls[j].p2.y << 2);
			draw_line(w, r);
			j++;
		}
		i++;
	}
	j = 0;
	while (j < r->sectors[r->player.sector].wall_count)
	{
		r->x_1 = 10 + ((int)r->sectors[r->player.sector].walls[j].p1.x << 2);
		r->y_1 = 10 + ((int)r->sectors[r->player.sector].walls[j].p1.y << 2);
		r->x_2 = 10 + ((int)r->sectors[r->player.sector].walls[j].p2.x << 2);
		r->y_2 = 10 + ((int)r->sectors[r->player.sector].walls[j].p2.y << 2);
		draw_line(w, r);
		j++;
	}
}

void	drawing(t_win *w, t_ray *r)
{
	ft_bzero(w->surface->pixels, ((WIN_W * WIN_H) << 2));
	draw_player_view(w, r);
	// draw_minimap(w, r);
	SDL_UpdateWindowSurface(w->win);
	printf("%f ; %d\n", (float)(1.0 / w->fps), w->fps);
}

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
		if (is_key_pressed(&k) > 0)
		{
			handle_keyboard_mvt(w, r, &k);
		}
		drawing(w, r);
		fps_count(w);
	}
}

int		main(void)
{
	t_ray	r;
	t_win	w;

	init_t_ray(&r);
	r.sectors = map();
	r.sector_count = 14;
	r.player.sector = 0;
	r.player.position.z = 32;
	init_sdl(&w);
	w.old_time	= 0.0;
	w.time		= 0.0;
	sdl_loop(&w, &r);
	return (0);
}
