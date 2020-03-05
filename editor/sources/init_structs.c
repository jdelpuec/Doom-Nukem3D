/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:43:49 by lubernar          #+#    #+#             */
/*   Updated: 2020/03/05 16:08:19 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_elem		init_elem(void)
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

void		init_edit(t_editor *edit)
{
	edit->gravity = 2;
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

void		init_textures2(t_editor *edit)
{
	char		**tab_sprite;
	char		**gravity;

	if (!(gravity = (char **)malloc(sizeof(char*) * 3)))
		exit(0);
	gravity[0] = "./ress/mooon.bmp";
	gravity[1] = "./ress/earth.bmp";
	gravity[2] = NULL;
	edit->list_gravity = handle_textures(gravity, -1);
	free(gravity);
	edit->list_gravity.id == -1 ? exit(0) : 0;
	if (!(tab_sprite = (char **)malloc(sizeof(char*) * 3)))
		exit(0);
	tab_sprite[0] = "./ress/noodles.bmp";
	tab_sprite[1] = "./ress/baguettes.bmp";
	tab_sprite[2] = NULL;
	edit->list_sprite = handle_textures(tab_sprite, -1);
	free(tab_sprite);
	edit->list_sprite.id == -1 ? exit(0) : 0;
}

void		init_textures(t_editor *edit)
{
	char		**tab;
	char		**tab_player;

	init_textures2(edit);
	if (!(tab_player = (char **)malloc(sizeof(char*) * 2)))
		exit(0);
	tab_player[0] = "./ress/naruto.bmp";
	tab_player[1] = NULL;
	edit->list_player = handle_textures(tab_player, -1);
	free(tab_player);
	edit->list_player.id == -1 ? exit(0) : 0;
	if (!(tab = (char **)malloc(sizeof(char*) * 5)))
		exit(0);
	tab[0] = "./ress/Bamboo.bmp";
	tab[1] = "./ress/wood2.bmp";
	tab[2] = "./ress/wood.bmp";
	tab[3] = "./ress/arrows.bmp";
	tab[4] = NULL;
	edit->list = handle_textures(tab, -1);
	free(tab);
	edit->list.id == -1 ? exit(0) : 0;
}
