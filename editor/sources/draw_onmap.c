/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_onmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:01:09 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/08 15:32:42 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"

void	player_sprites_coord(t_editor *edit, t_sdl *sdl)
{
	if (edit->player_selected)
	{
		draw_redsquare(sdl, W / 1.45, 450);
		edit->texture_choosen = 0;
		edit->sprite_choosen = 0;
		if (sdl->e.type == SDL_MOUSEBUTTONDOWN && sdl->xmouse <= (W / 1.5) - 11
		&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11)
		{
			edit->play_x = sdl->xmouse - 15;
			edit->play_y = sdl->ymouse - 15;
			edit->player_onmap = 1;
		}
	}
	if (edit->sprite_choosen != 0)
	{
		if (sdl->e.type == SDL_MOUSEBUTTONDOWN && sdl->xmouse <= (W / 1.5) - 11
		&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11)
		{
			edit->sprite_x = sdl->xmouse - 15;
			edit->sprite_y = sdl->ymouse - 15;
		}
	}
}

void	choosen_texture(t_sdl *sdl, t_editor *edit)
{
	if (edit->texture_choosen == 1)
		draw_redsquare(sdl, W / 1.45, 112);
	else if (edit->texture_choosen == 2)
		draw_redsquare(sdl, (W / 1.45) + 86, 112);
	else if (edit->texture_choosen == 3)
		draw_redsquare(sdl, (W / 1.45) + 170, 112);
	else if (edit->texture_choosen == 4)
		draw_redsquare(sdl, (W / 1.45) + 240, 112);
	else if (edit->texture_choosen == 5)
		draw_redsquare(sdl, (W / 1.45) + 320, 112);
}

void	find_walls_coord(t_sdl *sdl, t_editor *edit, t_line *line, t_lst **lst)
{
	choosen_texture(sdl, edit);
	if (edit->nb_clic == 1)
		draw_line_on_click(line, sdl, edit);
	else if (edit->nb_clic >= 2)
	{
		line->x1 = edit->x2_replace;
		line->y1 = edit->y2_replace;
		line->x2 = sdl->xmouse;
		line->y2 = sdl->ymouse;
		draw_line(line, sdl);
		if (sdl->e.type == SDL_MOUSEBUTTONDOWN && sdl->xmouse <= (W / 1.5) - 11
		&& sdl->xmouse >= 11 && sdl->ymouse >= 11 && sdl->ymouse <= H - 11
		&& edit->pressed != 1 && edit->nb_clic > 2)
		{
			edit->pressed = 1;
			find_coordinates2(sdl, edit);
			if (edit->x2_replace != line->x1 || edit->y2_replace != line->y1)
				push_back_withoux1(*lst, edit, line);
		}
	}
}

void	draw_line_lst(t_line *line2, t_elem *begin, t_sdl *sdl)
{
	line2->x1 = begin->x1;
	line2->y1 = begin->y1;
	line2->x2 = begin->x2;
	line2->y2 = begin->y2;
	draw_line(line2, sdl);
}

void	draw_walls_lst(t_elem *begin, t_lst **lst, t_sdl *sdl)
{
	t_line line2;

	if (begin->next == NULL && (*lst)->first != NULL)
		draw_line_lst(&line2, begin, sdl);
	while (begin->next != NULL && (*lst)->first != NULL)
	{
		draw_line_lst(&line2, begin, sdl);
		begin = begin->next;
		if (begin->next == NULL && (*lst)->first != NULL)
			draw_line_lst(&line2, begin, sdl);
	}
}
