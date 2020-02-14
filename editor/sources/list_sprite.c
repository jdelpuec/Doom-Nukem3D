/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:27:06 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/14 11:09:07 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"
#include "../includes/list.h"

t_text_tab	display_next(t_sdl *sdl, t_sprite *s, t_text_tab tmp, t_editor *e)
{
	if (s->num_sprite == 1)
	{
		e->noodles = 1;
		display(s->x, s->y, sdl, e->list_sprite);
	}
	if (s->num_sprite == 2)
	{
		e->baguettes = 1;
		if (tmp.next != NULL)
			tmp = *tmp.next;
		display(s->x, s->y, sdl, tmp);
	}
	return (tmp);
}

void	init_sprite(t_lst_sprite *l)
{
	l->first = NULL;
	l->last = NULL;
}

void	push_back_sprite(t_lst *l, t_editor *edit)
{
	t_sprite	*nouv;
	if (edit->nb_sprites < 20)
	{
		nouv = malloc(sizeof(t_sprite));
		if (!nouv)
			exit(0);
		nouv->x = edit->sprite_x;
		nouv->y = edit->sprite_y;
		nouv->num_sprite = edit->sprite_choosen;
		nouv->nb_maillon++;
		nouv->prev = l->lst_s->last;
		nouv->next = NULL;
		edit->nb_sprites++;
		if (edit->sprite_choosen == 1 || edit->sprite_choosen == 2)
			nouv->pickable = 1;
		else
			nouv->pickable = 0;
		if (l->lst_s->last)
			l->lst_s->last->next = nouv;
		else
			l->lst_s->first = nouv;
		l->lst_s->last = nouv;
	}
}
