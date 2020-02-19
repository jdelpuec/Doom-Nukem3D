/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:28:38 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/19 14:27:33 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "malloc.h"

void		display(int x, int y, t_text_tab hud, t_win *win)
{
	int	text_x;
	int	text_y;
	int	tmp_x;
	int	tmp_y;

	tmp_x = x;
	tmp_y = y;
	text_x = 0;
	text_y = 0;
	while (x < tmp_x + hud.w)
	{
		y = tmp_y;
		text_y = 0;
		while (y < tmp_y + hud.h)
		{
			if (hud.data[(text_y * hud.w) + text_x] != 0x00ff00)
				*((int *)win->surface->pixels + (y * WIN_W + x)) =
				hud.data[(text_y * hud.h) + text_x];
			y++;
			text_y++;
		}
		x++;
		text_x++;
	}
}

t_text_tab	find(char *str)
{
	char		**nom;
	t_text_tab	hud;

	nom = (char **)malloc(sizeof(char*) * 2);
	nom[0] = str;
	nom[1] = NULL;
	hud = handle_textures(nom, -1);
	free(nom);
	return (hud);
}
