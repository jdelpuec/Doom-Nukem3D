/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:56:05 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/11 17:02:13 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"

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
	while (x < tmp_x + 30)
	{
		y = tmp_y;
		text_y = 0;
		while (y < tmp_y + 30)
		{
			if (tmp.data[(text_y * 30) + text_x] != 0x00ff00 && text_x >= 0
			&& text_x <= 30 && text_y >= 0 && text_y <= 30)
				*((int *)sdl->ren->pixels + (y * W + x)) =
				tmp.data[(text_y * 30) + text_x];
			y++;
			text_y++;
		}
		x++;
		text_x++;
	}
}

void	textures_display(t_sdl *sdl, t_editor *edit)
{
	t_text_tab	tmp_text;
	t_text_tab	tmp_sprites;

	tmp_sprites = edit->list_sprite;
	display(W / 1.45, 210, sdl, tmp_sprites);
	tmp_sprites = *tmp_sprites.next;
	display((W / 1.45) + 86, 210, sdl, tmp_sprites);
	display(W / 1.45, 450, sdl, edit->list_player);
	tmp_text = edit->list;
	display(W / 1.45, 112, sdl, tmp_text);
	tmp_text = *tmp_text.next;
	display((W / 1.45) + 86, 112, sdl, tmp_text);
	tmp_text = *tmp_text.next;
	display((W / 1.45) + 170, 112, sdl, tmp_text);
	tmp_text = *tmp_text.next;
	display((W / 1.45) + 520, 65, sdl, tmp_text);
	// tmp_text = *tmp_text.next;
	// display((W / 1.45) + 320, 112, sdl, tmp_text);
	// tmp_text = *tmp_text.next;
	// display((W / 1.45) + 520, 65, sdl, tmp);
	if (edit->player_onmap)
		display(edit->play_x, edit->play_y, sdl, edit->list_player);
}