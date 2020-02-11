/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/11 15:47:07 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "doom.h"
#include "raycasting.h"
#include "draw.h"
#include "init.h"
#include "event.h"

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

	w.text_list = init_text();


	init_sdl(&w);
	sdl_loop(&w, &r);
	return (0);
}
