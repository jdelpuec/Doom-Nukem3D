/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:20:48 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/15 18:50:48 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"

void		display_l(int x, int y, t_win *sdl, t_text_tab tmp)
{
	int	text_x;
	int text_y;
	int	tmp_x;
	int	tmp_y;

	tmp_x = x;
	tmp_y = y;
	text_x = 0;
	text_y = 0;
	while (x < tmp_x + tmp.w)
	{
		y = tmp_y;
		text_y = 0;
		while (y < tmp_y + tmp.h)
		{
			if (tmp.data[(text_y * tmp.w) + text_x] != 0x00ff00)
				*((int *)sdl->surface->pixels + (y * WIN_W + x)) =
				tmp.data[(text_y * tmp.h) + text_x];
			y++;
			text_y++;
		}
		x++;
		text_x++;
	}
}

void		init_inventory(t_invent *inv)
{
	int	i;

	i = 0;
	inv->nb_noodles = 0;
	inv->nb_baguette = 0;
	inv->nb_noodles_c = 0;
	inv->invent.inventory = (char**)malloc(sizeof(char*) * 4);
	inv->invent.inventory[0] = "ress/noodles.bmp";
	inv->invent.inventory[1] = "ress/baguettes.bmp";
	inv->invent.inventory[2] = "ress/noodlescomplete.bmp";
	inv->invent.inventory[3] = NULL;
	while (i < 4)
	{
		inv->invent.inventory_display[i] = (int)malloc(sizeof(int));
		inv->invent.inventory_display[i] = 0;
		i++;
	}
}

void		if_player_on_sprites(t_ray *r, t_win *sdl, int i)
{
	if (r->player.position.x >= r->inv.sprite[i].pos.x - 1
	&& r->player.position.x <= r->inv.sprite[i].pos.x + 1
	&& r->player.position.y >= r->inv.sprite[i].pos.y - 1
	&& r->player.position.y <= r->inv.sprite[i].pos.y + 1)
	{
		if (r->inv.sprite[i].id == 1 && r->inv.sprite[i].pickable == 1)
		{
			r->inv.invent.inventory_display[0] = 1;
			r->inv.sprite[i].pickable = 0;
			r->inv.nb_noodles++;
		}
		if (r->inv.sprite[i].id == 2 && r->inv.sprite[i].pickable == 1)
		{
			r->inv.invent.inventory_display[1] = 1;
			r->inv.sprite[i].pickable = 0;
			r->inv.nb_baguette++;
		}
		if (r->inv.sprite[i].id == 3 && sdl->reload == 0)
		{
			sdl->fired = 2;
			sdl->reload = 1;
			sdl->old_t = SDL_GetTicks();
			r->inv.nb_bullet += 100;
		}
	}
}

void		display_inventory(t_win *sdl, t_ray *r, int *j)
{
	if (*j == 0)
	{
		r->inv.list = handle_textures(r->inv.invent.inventory, 0);
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
	if (r->inv.invent.inventory_display[2] == 1)
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
