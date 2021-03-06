/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:27:26 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/04/14 21:35:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "ft_math.h"

t_text_tab	init_text(void)
{
	t_text_tab	text_list;
	char		**tab;

	tab = (char **)malloc(sizeof(char*) * 6);
	tab[0] = "./ressources/textures/Bamboo.bmp";
	tab[1] = "./ressources/textures/wood.bmp";
	tab[2] = "./ressources/textures/wood2.bmp";
	tab[3] = "./ressources/textures/tree.bmp";
	tab[4] = "./ressources/textures/wall.bmp";
	tab[5] = NULL;
	text_list = handle_textures(tab, -1);
	free(tab);
	text_list.id == -1 ? exit(0) : 0;
	if (text_list.id == -1)
	{
		ft_putendl("Textures failed to load, please check your paths. \n");
		exit(0);
	}
	return (text_list);
}

void		init_sdl(t_win *w)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		ft_putstr(SDL_GetError());
	w->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED
	, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
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
	w->hud = find("ressources/hud/health.bmp");
	w->hud2 = find("ressources/hud/ammo_copy.bmp");
	w->hud3 = find("ressources/hud/inventory.bmp");
	w->old_time = 0.0;
	w->time = 0.0;
	w->text_list = init_text();
	w->reload = 0;
	w->fired = 0;
	w->old_t = 0.0;
}

void		init_t_ray(t_ray *r, t_env *env)
{
	int	i;

	i = -1;
	r->dist_pp = WIN_W / tanf(deg_to_rad(30.0));
	r->last_sec = -2;
	r->speed = 5.0;
	r->thresh = 1;
	r->inv.nb_bullet = 50;
	r->inv.nb_hp = 20;
	r->inv.anim = 0;
	r->inv.nb_sprites = env->sprites;
	r->inv.nb_sprites > 0 ? r->inv.sprite = env->spt : 0;
	r->gun = init_gun();
	r->sectors = env->sct;
	r->player = env->player;
	r->sector_count = env->room;
	r->space = r->sector_count > 1 ? 1.8 : 4;
	r->gravity = r->player.gravity;
	r->start_pos = r->player;
}
