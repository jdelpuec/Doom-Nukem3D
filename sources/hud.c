/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:22:11 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/19 15:31:32 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void		apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, dest, &offset);
	SDL_FreeSurface(source);
	SDL_FreeSurface(dest);
}

void		init_ttf(t_win *sdl)
{
	if (TTF_Init() == -1)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("TTF Error.\n");
	}
	sdl->font = TTF_OpenFont("./font/tf2build.ttf", 31);
	if (!sdl->font)
		exit(0);
	sdl->font2 = TTF_OpenFont("./font/tf2build.ttf", 12);
	if (!sdl->font2)
		exit(0);
	sdl->fc.r = 0xFF;
	sdl->fc.g = 0xA5;
	sdl->fc.b = 0x00;
	sdl->fc.a = 0xFF;
}

void		hud_text(t_ray *r, t_win *sdl)
{
	char *tmp_nb_noodles;
	char *tmp_nb_baguette;

	if (r->inv.nb_noodles > 0)
	{
		tmp_nb_noodles = ft_itoa(r->inv.nb_noodles);
		sdl->mes = TTF_RenderText_Solid(sdl->font2, tmp_nb_noodles, sdl->fc);
		if (sdl->mes == NULL)
			return ;
		apply_surface((WIN_W - 15), (WIN_H / 2 + 100), sdl->mes, sdl->surface);
		free(tmp_nb_noodles);
	}
	if (r->inv.nb_baguette > 0)
	{
		tmp_nb_baguette = ft_itoa(r->inv.nb_baguette);
		sdl->mes = TTF_RenderText_Solid(sdl->font2, tmp_nb_baguette, sdl->fc);
		if (sdl->mes == NULL)
			return ;
		apply_surface((WIN_W - 15), (WIN_H / 2 + 40), sdl->mes, sdl->surface);
		free(tmp_nb_baguette);
	}
}

void		hud_textures(t_win *sdl, t_ray *r)
{
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
	hud_text(r, sdl);
}

void		hud(t_win *sdl, t_ray *r)
{
	char *tmp_hp;
	char *tmp_bullet;
	char *tmp_nb_noodles_c;

	tmp_hp = ft_itoa(r->inv.nb_hp);
	tmp_bullet = ft_itoa(r->inv.nb_bullet);
	sdl->mes = TTF_RenderText_Solid(sdl->font, tmp_hp, sdl->fc);
	free(tmp_hp);
	if (sdl->mes == NULL)
		return ;
	apply_surface((WIN_W / 30), 565, sdl->mes, sdl->surface);
	sdl->mes = TTF_RenderText_Solid(sdl->font, tmp_bullet, sdl->fc);
	free(tmp_bullet);
	if (sdl->mes == NULL)
		return ;
	hud_textures(sdl, r);
	if (r->inv.nb_noodles_c > 0)
	{
		tmp_nb_noodles_c = ft_itoa(r->inv.nb_noodles_c);
		sdl->mes = TTF_RenderText_Solid(sdl->font2, tmp_nb_noodles_c, sdl->fc);
		if (sdl->mes == NULL)
			return ;
		apply_surface((WIN_W - 75), (WIN_H / 2 + 40), sdl->mes, sdl->surface);
		free(tmp_nb_noodles_c);
	}
}
