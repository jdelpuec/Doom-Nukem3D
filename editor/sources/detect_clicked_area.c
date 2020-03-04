/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_clicked_area.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:40:36 by lubernar          #+#    #+#             */
/*   Updated: 2020/03/02 17:16:04 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		display_sprite(t_lst **lst, t_sprite *s, t_sdl *sdl, t_editor *e)
{
	t_text_tab	tmp;

	tmp = e->list_sprite;
	while ((*lst)->lst_s->first != NULL && s->next != NULL)
	{
		tmp = display_next(sdl, s, tmp, e);
		s = s->next;
		tmp = display_next(sdl, s, tmp, e);
		if (s->next == NULL)
		{
			if (s->num_sprite == 1)
			{
				e->noodles = 1;
				display(s->x, s->y, sdl, e->list_sprite);
			}
			else if (s->num_sprite == 2)
			{
				e->baguettes = 1;
				display(s->x, s->y, sdl, tmp);
			}
		}
	}
}

void		find_sprites_coord(t_lst **lst, t_editor *edit, t_sdl *sdl)
{
	t_sprite	*sprite;
	t_text_tab	tmp;

	if (sdl->e.type == SDL_MOUSEBUTTONDOWN && sdl->xmouse <= (W / 1.5) - 11
	&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11
	&& edit->sprite_choosen != 0 && edit->pressed == 0)
	{
		push_back_sprite((*lst), edit);
		edit->pressed = 1;
	}
	tmp = edit->list_sprite;
	if ((*lst)->lst_s->first != NULL)
		sprite = (*lst)->lst_s->first;
	if ((*lst)->lst_s->first != NULL && sprite->next == NULL)
		display_next(sdl, sprite, tmp, edit);
	if ((*lst)->lst_s->first != NULL)
		display_sprite(lst, sprite, sdl, edit);
}

void		init_other_text(t_editor *e, int p_sele, int t_choos, int s_choos)
{
	e->player_selected = p_sele;
	e->texture_choosen = t_choos;
	e->sprite_choosen = s_choos;
}

void		textures_area2(t_sdl *sdl, t_editor *edit)
{
	if (sdl->e.motion.x >= (W / 1.45) + 240 && sdl->e.motion.x
	<= (W / 1.45) + 270 && sdl->e.motion.y >= 112
	&& sdl->e.motion.y <= 142 && edit->sector_num < 1)
		init_other_text(edit, 0, 4, 0);
	if (sdl->e.motion.x >= (W / 1.45) + 320 && sdl->e.motion.x
	<= (W / 1.45) + 350 && sdl->e.motion.y >= 112
	&& sdl->e.motion.y <= 142 && edit->sector_num < 1)
		init_other_text(edit, 0, 5, 0);
	if (sdl->e.motion.x >= (W / 1.45) && sdl->e.motion.x
	<= (W / 1.45) + 30 && sdl->e.motion.y >= 210
	&& sdl->e.motion.y <= 240 && edit->nb_clic == 0)
		init_other_text(edit, 0, 0, 1);
	if (sdl->e.motion.x >= (W / 1.45) + 86 && sdl->e.motion.x
	<= (W / 1.45) + 116 && sdl->e.motion.y >= 210
	&& sdl->e.motion.y <= 240 && edit->nb_clic == 0)
		init_other_text(edit, 0, 0, 2);
}

void		textures_area(t_sdl *sdl, t_editor *edit)
{
	if (sdl->e.motion.x >= (W / 1.45) && sdl->e.motion.x
	<= (W / 1.45) + 36 && sdl->e.motion.y >= 320
	&& sdl->e.motion.y <= 356 && edit->nb_clic == 0)
		edit->gravity = 1;
	if (sdl->e.motion.x >= (W / 1.45) + 108 && sdl->e.motion.x
	<= (W / 1.45) + 145 && sdl->e.motion.y >= 320
	&& sdl->e.motion.y <= 356 && edit->nb_clic == 0)
		edit->gravity = 2;
	if (sdl->e.motion.x >= W / 1.45 && sdl->e.motion.x <= (W / 1.45)
	+ 30 && sdl->e.motion.y >= 112 && sdl->e.motion.y <= 142
	&& edit->sector_num < 1)
		init_other_text(edit, 0, 1, 0);
	if (sdl->e.motion.x >= (W / 1.45) + 86 && sdl->e.motion.x
	<= (W / 1.45) + 116 && sdl->e.motion.y >= 112
	&& sdl->e.motion.y <= 142 && edit->sector_num < 1)
		init_other_text(edit, 0, 2, 0);
	if (sdl->e.motion.x >= (W / 1.45) + 170 && sdl->e.motion.x
	<= (W / 1.45) + 200 && sdl->e.motion.y >= 112
	&& sdl->e.motion.y <= 142 && edit->sector_num < 1)
		init_other_text(edit, 0, 3, 0);
	textures_area2(sdl, edit);
}
