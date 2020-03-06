/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:49:14 by siwarin           #+#    #+#             */
/*   Updated: 2020/03/06 11:45:50 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"
#include "init.h"
#include "event.h"

void	fps_count(t_win *w)
{
	float delta;

	w->old_time = w->time;
	w->time = SDL_GetTicks();
	delta = (w->time - w->old_time) / 1000.0;
	w->fps = (int)(1.0 / delta);
}

void	sdl_loop(t_win *w, t_ray *r)
{
	t_keyboard k;

	init_keyboard(&k);
	while (1)
	{
		w->jpressed = 0;
		while (SDL_PollEvent(&w->e))
		{
			if (w->e.type == SDL_KEYDOWN || w->e.type == SDL_KEYUP)
				if (handle_keyboard_event(w, &k) < 0)
					return ;
			mouse_button_down(w, r);
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

int		main(int ac, char **av)
{
	t_ray r;
	t_win w;
	t_env env;

	if (ac != 2)
	{
		ft_putendl("N'oubliez pas la map !");
		exit(0);
	}
	if (parsing(av[1], &env) == -1)
	{
		ft_putstr("PARSING ISSUE\n");
		exit(0);
	}
	w.text_list = init_text();
	init_t_ray(&r, &env);
	init_ttf(&w);
	init_sdl(&w);
	FMOD_System_PlaySound(w.s.fmod, FMOD_CHANNEL_FREE, w.s.music, 0, NULL);
	FMOD_Sound_SetLoopCount(w.s.music, -1);
	sdl_loop(&w, &r);
	return (0);
}
