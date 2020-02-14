/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:20:48 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/14 18:22:39 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"
#include "inventory.h"

void	display_l(int x, int y, t_win *sdl, t_text_tab tmp)
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

t_invent	*inventory(t_ray *r, t_win *sdl, t_invent *inv)
{
	int	i;
	static int j;

	i = 0;
	// printf("pos x : %f\n", r->player.position.x);
	// printf("pos y : %f\n", r->player.position.y);
	if (j == 0)
	{
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
	i = 0;
	while (i < r->inv.nb_sprites)
	{
		if (r->player.position.x >= inv->sprite[i].pos.x - 1 && r->player.position.x <= inv->sprite[i].pos.x + 1
		&& r->player.position.y >= inv->sprite[i].pos.y - 1 && r->player.position.y <= inv->sprite[i].pos.y + 1)
		{
			if (inv->sprite[i].id == 1 && inv->sprite[i].pickable == 1)
			{
				inv->invent.inventory_display[0] = 1;
				inv->sprite[i].pickable = 0;
				inv->nb_noodles++;
			}
			if (inv->sprite[i].id == 2 && inv->sprite[i].pickable == 1)
			{
				inv->invent.inventory_display[1] = 1;
				inv->sprite[i].pickable = 0;
				inv->nb_baguette++;
			}
		}
		i++;
	}
	if ((inv->invent.inventory_display[0] == 1
	&& inv->invent.inventory_display[1] == 1) || (inv->nb_noodles > 0 && inv->nb_baguette > 0))
	{
		inv->invent.inventory_display[0] = 0;
		inv->invent.inventory_display[1] = 0;
		inv->invent.inventory_display[2] = 1;
		inv->nb_noodles_c++;
		inv->nb_noodles--;
		inv->nb_baguette--;
	}
	if (j == 0)
	{
		inv->list = handle_textures(inv->invent.inventory, 0);
		free(inv->invent.inventory);
	}
	inv->list.data == NULL ? exit(0) : 0;
	j = 1;
	inv->list.w = 30;
	inv->list.h = 30;
	if (inv->invent.inventory_display[0] == 1 || inv->nb_noodles > 0)
		display_l((WIN_W - 43), (WIN_H / 2 + 75), sdl, inv->list);
	if (inv->invent.inventory_display[1] == 1 || inv->nb_baguette > 0)
	{
		r->inv.tmp = *inv->list.next;
		r->inv.tmp.w = 30;
		r->inv.tmp.h = 30;
		display_l((WIN_W - 40), (WIN_H / 2) + 17, sdl, r->inv.tmp);
	}
	if (inv->invent.inventory_display[2] == 1)
	{
		r->inv.tmp = *inv->list.next->next;
		r->inv.tmp.w = 30;
		r->inv.tmp.h = 30;
		display_l((WIN_W - 100), (WIN_H / 2) + 17, sdl, r->inv.tmp);
	}
	return (inv);
}
