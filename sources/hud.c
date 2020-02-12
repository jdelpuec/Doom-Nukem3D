/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:22:11 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/12 18:01:23 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "doom.h"
#include "malloc.h"

void    display(int x, int y, t_text_tab hud, t_win *win)
{
    int text_x;
    int text_y;
    int tmp_x;
    int tmp_y;
    tmp_x = x;
    tmp_y = y;
    text_x = 0;
    text_y = 0;
    while (x < tmp_x + 64)
    {
        y = tmp_y;
        text_y = 0;
        while (y < tmp_y + 64)
        {
            if (hud.data[(text_y * 64) + text_x] != 0x00ff00)
              *((int *)win->surface->pixels + (y * WIN_W + x)) =
              hud.data[(text_y * 64) + text_x];
            y++;
            text_y++;
        }
        x++;
        text_x++;
    }
}

t_text_tab	find(char *str)
{
  char **nom;
  t_text_tab hud;

	nom = (char **)malloc(sizeof(char*) * 2);
	nom[0] = str;
	nom[1] = NULL;
	hud = handle_textures2(nom, 0);
	free(nom);
  return hud;
}

void	hud(t_win *sdl)
{
  display(20, WIN_H - 84, sdl->hud, sdl);
  display(WIN_W - 84, WIN_H - 84, sdl->hud2, sdl);
}
