/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:20:48 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/08 15:07:43 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../includes/Doom_Nukem.h"

typedef struct		s_parsing_sprite
{
	int					x;
	int					y;
	int					z;
	int					num_sprite;
	int					nb_maillon;
	int					pickable;
}					t_parsing_sprite;

void	display(int x, int y, t_sdl *sdl, t_text_tab tmp)
{
	int	text_x;
	int text_y;
	int	tmp_x;
	int	tmp_y;

	tmp_x = x;
	tmp_y = y;
	text_x = 0;
	text_y = 0;
	while (x < tmp_x + 60)
	{
		y = tmp_y;
		text_y = 0;
		while (y < tmp_y + 60)
		{
			*((int *)sdl->ren->pixels + (y * W + x)) =
			tmp.data[(text_y * 60) + text_x];
			y++;
			text_y++;
		}
		x++;
		text_x++;
	}
}

void	inventory_display(t_inventory *invent)
{
	t_text_tab	list;
	t_sdl sdl;

	list = handle_textures(invent->inventory, 0);
	if (invent->inventory_display[0] == 1)
		display(200, 300, &sdl, list);
}

void	inventory(t_player *p, t_parsing_sprite *sprite, t_inventory *invent)
{
	int	i;

	i = 0;
	invent->inventory = (char**)malloc(sizeof(char*) * 2);
	invent->inventory[0] = "../ress/bullet.bmp";
	invent->inventory[1] = NULL;
	while (i < 4)
	{
		invent->inventory_display[i] = (int)malloc(sizeof(int));
		invent->inventory_display[i] = 0;
		i++;
	}
	if (p->position.x == sprite->x && p->position.y == sprite->y
	&& sprite->num_sprite == 1 && sprite->pickable)
	{
		invent->inventory_display[0] = 1;
	}
}
