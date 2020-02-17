/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:43:49 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/17 16:44:31 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"

t_elem	init_elem(void)
{
	t_elem	elem;

	elem.nb_maillon = 0;
	elem.x1 = 0;
	elem.y1 = 0;
	elem.x2 = 0;
	elem.y2 = 0;
	elem.num_text = 0;
	elem.next = NULL;
	elem.prev = NULL;
	return (elem);
}

t_sprite	init_sprites(void)
{
	t_sprite	sprite;

	sprite.nb_maillon = 0;
	sprite.x = 0;
	sprite.y = 0;
	sprite.pickable = 0;
	return (sprite);
}

void	init_edit(t_editor *edit)
{
	edit->gravity = 1;
	edit->nb_sprites = 0;
	edit->noodles = 0;
	edit->baguettes = 0;
	edit->lst_init = 0;
	edit->count_walls = 0;
	edit->nb_maillon = 0;
	edit->saved = 0;
	edit->nb_clic = 0;
	edit->texture_choosen = 0;
	edit->sector_num = 0;
	edit->pressed = 0;
	edit->player_selected = 0;
	edit->player_onmap = 0;
	edit->walls_h = 60;
	edit->sprite_choosen = 0;
}
