/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:22:11 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/14 18:00:04 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "doom.h"
#include "malloc.h"
#include "raycasting.h"

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
  char **nom;
  t_text_tab hud;

	nom = (char **)malloc(sizeof(char*) * 2);
	nom[0] = str;
	nom[1] = NULL;
	hud = handle_textures2(nom, 0);
	free(nom);
  return hud;
}

void	apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, dest, &offset);
	SDL_FreeSurface(source);
	SDL_FreeSurface(dest);
}

void init_ttf(t_win *sdl)
{
  if (TTF_Init() == -1)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("TTF Error.\n");
	}
	sdl->font = TTF_OpenFont("./font/tf2build.ttf", 31);
	if (!sdl->font)
		printf("TTF_OpenFont : %s\n", TTF_GetError());
  sdl->font2 = TTF_OpenFont("./font/tf2build.ttf", 12);
	if (!sdl->font2)
		printf("TTF_OpenFont : %s\n", TTF_GetError());
	sdl->fc.r = 0xFF;
	sdl->fc.g = 0xA5;
	sdl->fc.b = 0x00;
	sdl->fc.a = 0xFF;
}

void	hud(t_win *sdl, t_invent *inv, t_ray *r)
{
  char *tmp_hp;
  char *tmp_bullet;
  char *tmp_nb_noodles;
  char *tmp_nb_baguette;
  char *tmp_nb_noodles_c;

  tmp_nb_baguette = ft_itoa(inv->nb_baguette);
  tmp_nb_noodles_c = ft_itoa(inv->nb_noodles_c);
	tmp_nb_noodles = ft_itoa(r->inv.nb_noodles);
  tmp_hp = ft_itoa(inv->nb_hp);
  tmp_bullet = ft_itoa(inv->nb_bullet);
  sdl->mes = TTF_RenderText_Solid(sdl->font, tmp_hp, sdl->fc);
  free(tmp_hp);
	if (sdl->mes == NULL)
		return ;
	apply_surface((WIN_W / 30), 565, sdl->mes, sdl->surface);
  sdl->mes = TTF_RenderText_Solid(sdl->font, tmp_bullet, sdl->fc);
  free(tmp_bullet);
	if (sdl->mes == NULL)
		return ;
	apply_surface((WIN_W - 80), 565, sdl->mes, sdl->surface);
  sdl->hud.w = 64;
  sdl->hud.h = 64;
  display(20, WIN_H - 84, sdl->hud, sdl);
  sdl->hud2.w = 64;
  sdl->hud2.h = 64;
  display(WIN_W - 84, WIN_H - 84, sdl->hud2, sdl);
  sdl->hud3.w = 120;
  sdl->hud3.h = 120;
  display(WIN_W - 120, WIN_H / 2, sdl->hud3, sdl);
  if (r->inv.nb_noodles > 0)
  {
    sdl->mes = TTF_RenderText_Solid(sdl->font2, tmp_nb_noodles, sdl->fc);
    if (sdl->mes == NULL)
      return ;
    apply_surface((WIN_W - 15), (WIN_H / 2 + 100), sdl->mes, sdl->surface);
    free(tmp_nb_noodles);
  }
  if (inv->nb_baguette > 0)
  {
    sdl->mes = TTF_RenderText_Solid(sdl->font2, tmp_nb_baguette, sdl->fc);
    if (sdl->mes == NULL)
      return ;
    apply_surface((WIN_W - 15), (WIN_H / 2 + 40), sdl->mes, sdl->surface);
    free(tmp_nb_baguette);
  }
  if (inv->nb_noodles_c > 0)
  {
    sdl->mes = TTF_RenderText_Solid(sdl->font2, tmp_nb_noodles_c, sdl->fc);
    if (sdl->mes == NULL)
      return ;
    apply_surface((WIN_W - 75), (WIN_H / 2 + 40), sdl->mes, sdl->surface);
    free(tmp_nb_noodles_c);
  }
}
