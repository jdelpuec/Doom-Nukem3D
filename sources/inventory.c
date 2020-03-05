/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:20:48 by lubernar          #+#    #+#             */
/*   Updated: 2020/03/05 12:52:33 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void		init_inventory(t_invent *inv)
{
	int	i;

	i = -1;
	inv->nb_noodles = 0;
	inv->nb_baguette = 0;
	inv->nb_noodles_c = 0;
	inv->invent.inventory = (char**)malloc(sizeof(char*) * 4);
	inv->invent.inventory[0] = "./ressources/noodles.bmp";
	inv->invent.inventory[1] = "./ressources/baguettes.bmp";
	inv->invent.inventory[2] = "./ressources/noodlescomplete.bmp";
	inv->invent.inventory[3] = NULL;
	while (++i < 4)
		inv->invent.inventory_display[i] = 0;
}

void		display_to_true(t_ray *r, int i, int j)
{
	r->inv.invent.inventory_display[j] = 1;
	r->inv.sprite[i].pickable = 0;
	r->inv.sprite[i].id == 1 ? r->inv.nb_noodles++ : 0;
	r->inv.sprite[i].id == 2 ? r->inv.nb_baguette++ : 0;
}

void		if_player_on_sprites(t_ray *r, t_win *sdl, int i)
{
	if (r->player.position.x >= r->inv.sprite[i].pos.x - 1
	&& r->player.position.x <= r->inv.sprite[i].pos.x + 1
	&& r->player.position.y >= r->inv.sprite[i].pos.y - 1
	&& r->player.position.y <= r->inv.sprite[i].pos.y + 1
	&& r->player.position.z - PLAY_H <= r->inv.sprite[i].pos.z +
	r->sectors[r->cur_sector].floor_height)
	{
		if (r->inv.sprite[i].id == 1 && r->inv.sprite[i].pickable == 1)
			display_to_true(r, i, 0);
		if (r->inv.sprite[i].id == 2 && r->inv.sprite[i].pickable == 1)
			display_to_true(r, i, 1);
		if (r->inv.sprite[i].id == 3 && sdl->reload == 0)
		{
			sdl->fired = 2;
			sdl->reload = 1;
			sdl->old_t = SDL_GetTicks();
			r->inv.nb_bullet += 100;
			FMOD_System_PlaySound(sdl->s.fmod, FMOD_CHANNEL_FREE
			, sdl->s.reload, 0, NULL);
		}
	}
}

void		display_inventory(t_win *sdl, t_ray *r, int *j)
{
	if (*j == 0)
	{
		r->inv.list = handle_textures(r->inv.invent.inventory, -1);
		free(r->inv.invent.inventory);
	}
	r->inv.list.data == NULL ? exit(0) : 0;
	*j = 1;
	r->inv.list.w = 30;
	r->inv.list.h = 30;
	if (r->inv.invent.inventory_display[0] == 1 || r->inv.nb_noodles > 0)
		display_l((WIN_W - 43), (WIN_H / 2 + 75), sdl, r->inv.list);
	if (r->inv.invent.inventory_display[1] == 1 || r->inv.nb_baguette > 0)
	{
		r->inv.tmp = *r->inv.list.next;
		r->inv.tmp.w = 30;
		r->inv.tmp.h = 30;
		display_l((WIN_W - 40), (WIN_H / 2) + 17, sdl, r->inv.tmp);
	}
	if (r->inv.invent.inventory_display[2] == 1 && r->inv.nb_noodles_c > 0)
	{
		r->inv.tmp = *r->inv.list.next->next;
		r->inv.tmp.w = 30;
		r->inv.tmp.h = 30;
		display_l((WIN_W - 100), (WIN_H / 2) + 17, sdl, r->inv.tmp);
	}
}

t_invent	*inventory(t_ray *r, t_win *sdl)
{
	int			i;
	static int	j;

	i = -1;
	j == 0 ? init_inventory(&r->inv) : 0;
	while (i++ < r->inv.nb_sprites)
		if_player_on_sprites(r, sdl, i);
	if ((r->inv.invent.inventory_display[0] == 1
	&& r->inv.invent.inventory_display[1] == 1)
	|| (r->inv.nb_noodles > 0 && r->inv.nb_baguette > 0))
	{
		r->inv.invent.inventory_display[0] = 0;
		r->inv.invent.inventory_display[1] = 0;
		r->inv.invent.inventory_display[2] = 1;
		r->inv.nb_noodles_c++;
		r->inv.nb_noodles--;
		r->inv.nb_baguette--;
	}
	display_inventory(sdl, r, &j);
	return (&r->inv);
}
