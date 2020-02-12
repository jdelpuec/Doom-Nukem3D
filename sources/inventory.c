/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:20:48 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/12 18:02:26 by lubernar         ###   ########.fr       */
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
	if (j == 0)
	{
		inv->sprite.nb_noodles = 0;
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
	if (r->player.position.x >= inv->sprite.x - 0.5 && r->player.position.x <= inv->sprite.x + 0.5
	&& r->player.position.y >= inv->sprite.y - 0.5 && r->player.position.y <= inv->sprite.y + 0.5
	&& inv->sprite.num_sprite == 1 && inv->sprite.pickable)
	{
		inv->invent.inventory_display[0] = 1;
		inv->sprite.pickable = 0;
	}
	// if (r->player.position.x >= inv->sprite.next->x - 0.5 && r->player.position.x <= inv->sprite.next->x + 0.5
	// && r->player.position.y >= inv->sprite.next->y - 0.5 && r->player.position.y <= inv->sprite.next->y + 0.5
	// && inv->sprite.next->num_sprite == 1 && inv->sprite.next->pickable)
	// {
	// 	inv->invent.inventory_display[1] = 1;
	// 	inv->sprite.next->pickable = 0;
	// }
	if (inv->invent.inventory_display[0] == 1 && inv->invent.inventory_display[1] == 1)
	{
		inv->invent.inventory_display[0] = 0;
		inv->invent.inventory_display[1] = 0;
		inv->invent.inventory_display[2] = 1;
		inv->sprite.nb_noodles++;
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
	if (inv->invent.inventory_display[0] == 1)
		display_l((WIN_W - 30), (WIN_H / 2) - 30, sdl, inv->list);
	return (inv);
}
