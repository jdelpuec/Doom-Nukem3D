/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:27:26 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/10 11:38:42 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"


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
	SDL_ShowCursor(0);
}

void	init_t_ray(t_ray *r)
{
	r->dist_pp	= WIN_W / tanf(deg_to_rad(30.0));
	r->last_sec = -2;
	r->speed	= 5.0;
	r->thresh	= 1;
}