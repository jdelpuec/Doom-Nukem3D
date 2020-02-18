/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editdraw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:23:14 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/18 11:53:10 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"
#include "../includes/list.h"

void	find_coordinates(t_sdl *sdl, t_editor *edit)
{
	edit->x1_replace = 10;
	edit->y1_replace = 10;
	while (edit->x1_replace < sdl->xmouse)
		edit->x1_replace += 20;
	if (edit->x1_replace > sdl->xmouse)
		edit->x1_replace -= 20;
	while (edit->y1_replace < sdl->ymouse)
		edit->y1_replace += 20;
	if (edit->y1_replace > sdl->ymouse)
		edit->y1_replace -= 20;
	edit->first_x = edit->x1_replace;
	edit->first_y = edit->y1_replace;
}

void	find_coordinates2(t_sdl *sdl, t_editor *edit)
{
	edit->x2_replace = 10;
	edit->y2_replace = 10;
	while (edit->x2_replace < sdl->xmouse)
		edit->x2_replace += 20;
	if (edit->x2_replace > sdl->xmouse)
		edit->x2_replace -= 20;
	while (edit->y2_replace < sdl->ymouse)
		edit->y2_replace += 20;
	if (edit->y2_replace > sdl->ymouse)
		edit->y2_replace -= 20;
}

void	clic(t_sdl *sdl, t_line *line, t_editor *edit, t_lst **lst)
{
	if (sdl->e.type == SDL_MOUSEBUTTONDOWN && sdl->xmouse <= (W / 1.5) - 11
	&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11
	&& edit->nb_clic == 0)
	{
		edit->nb_clic = 1;
		find_coordinates(sdl, edit);
	}
	else if (edit->nb_clic == 1 && sdl->xmouse <= (W / 1.5) - 11
	&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11)
	{
		if (sdl->e.type == SDL_MOUSEBUTTONDOWN && sdl->xmouse <= (W / 1.5) - 11
		&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11)
		{
			edit->nb_clic = 2;
			line->x2 = sdl->xmouse;
			line->y2 = sdl->ymouse;
			find_coordinates2(sdl, edit);
			if (edit->x1_replace != edit->x2_replace
			|| edit->y1_replace != edit->y2_replace)
				push_back(*lst, edit);
			else
				edit->nb_clic = 0;
		}
	}
}

void	editdraw(t_sdl *sdl, t_editor *edit, t_line *line, t_lst **lst)
{
	t_elem	begin;
	
	edit->vec.y = 37;
	edit->vec.x = 36;
	if ((*lst)->first != NULL)
		begin = *(*lst)->first;
	draw_menu(sdl);
	write_text(sdl, edit);
	textures_display(sdl, edit);
	player_sprites_coord(edit, sdl);
	find_sprites_coord(lst, edit, sdl);
	sdl->color = RED;
	if (edit->gravity == 1)
		draw_redsquare(sdl, (W / 1.45) + 107, 322, &edit->vec);
	else
		draw_redsquare(sdl, (W / 1.45), 320, &edit->vec);
	edit->vec.y = 30;
	edit->vec.x = 29;
	if (edit->sprite_choosen == 1)
		draw_redsquare(sdl, (W / 1.45), 210, &edit->vec);
	if (edit->sprite_choosen == 2)
		draw_redsquare(sdl, (W / 1.45) + 86, 210, &edit->vec);
	if (edit->texture_choosen && edit->sector_num < 1)
		find_walls_coord(sdl, edit, line, lst);
	draw_walls_lst(&begin, lst, sdl);
	if (edit->x2_replace == edit->first_x && edit->y2_replace
	== edit->first_y && edit->nb_clic > 1)
	{
		edit->nb_clic = 0;
		edit->sector_num++;
		init_lst_w(lst, edit);
	}
	if (edit->sector_num > 0 && edit->player_onmap && edit->noodles
	&& edit->baguettes)
		write_in_file(sdl, edit, lst);
	sdl->e.type == SDL_MOUSEBUTTONUP ? edit->pressed = 0 : 0;
}
