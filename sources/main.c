/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/16 14:41:10 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"
#include "draw.h"
#include "init.h"
#include "event.h"

void fps_count(t_win *w)
{
	float delta;

	w->old_time = w->time;
	w->time = SDL_GetTicks();
	delta = (w->time - w->old_time) / 1000.0;
	w->fps = (int)(1.0 / delta);
}

void sdl_loop(t_win *w, t_ray *r)
{
	t_keyboard k;

	init_keyboard(&k);
	while (1)
	{
		while (SDL_PollEvent(&w->e))
		{
			if (w->e.type == SDL_KEYDOWN || w->e.type == SDL_KEYUP)
				if (handle_keyboard_event(w, &k) < 0)
					return;
			if (w->e.type == SDL_MOUSEMOTION)
				handle_mouse_event(w, r);
			if (w->e.type == SDL_MOUSEBUTTONDOWN && w->fired == 0 && r->inv.nb_bullet > 0)
			{
				w->fired = 1;
				r->inv.nb_bullet--;
				w->old_t_f = SDL_GetTicks();
			}
		}
		if (is_key_pressed(&k) > 0 || r->player.position.z != r->sectors[r->cur_sector].floor_height + 32)
			handle_keyboard_mvt(w, r, &k);
		drawing(w, r, &k);
		fps_count(w);
	}
}

int main(int ac, char **av)
{
	t_ray r;
	t_win w;
	t_env env;
	(void)ac;

	if (ac != 2)
	{
		ft_putendl("la map idiot bete \n");
		exit(0);
	}
	if (parsing(av[1], &env) == -1)
		exit (0);
	r.inv.nb_sprites = env.sprites;
	r.inv.nb_bullet = 50;
	r.inv.nb_hp = 100;
	r.inv.anim = 0;
	w.text_list = init_text();


	r.sectors = env.sct;
	r.player = env.player;
	
	// r.sectors = map();
	// r.sector_count = 12;		// Brut map ---> need to implemant parsing
	// r.player.sector = 0;
	init_t_ray(&r);
	r.inv.nb_sprites = env.sprites;
	r.inv.sprite = env.spt;



	init_ttf(&w);
	init_sdl(&w);

	sdl_loop(&w, &r);
	return (0);
}
