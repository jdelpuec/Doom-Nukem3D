/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/21 13:17:13 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
				FMOD_System_PlaySound(w->s.fmod, FMOD_CHANNEL_FREE, w->s.shot, 0, NULL);
				w->fired = 1;
				r->inv.nb_bullet--;
				w->old_t_f = SDL_GetTicks();
			}
		}
		if (is_key_pressed(&k) > 0
		|| r->player.position.z != r->sectors[r->cur_sector].floor_height + 32)
			handle_keyboard_mvt(w, r, &k);
		drawing(w, r, &k);
		fps_count(w);
		if (w->e.type == SDL_QUIT)
			exit(0);
	}
}

int main(int ac, char **av)
{
	t_ray r;
	t_win w;
	t_env env;

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
	
	init_t_ray(&r, &env);

	init_ttf(&w);
	init_sdl(&w);
//	FMOD_System_PlaySound(w.s.fmod, FMOD_CHANNEL_FREE, w.s.music, 0, NULL);
//	FMOD_Sound_SetLoopCount(w.s.music, -1);
	sdl_loop(&w, &r);
	return (0);
}
