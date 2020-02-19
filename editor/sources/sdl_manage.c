/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:37:23 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/19 16:19:55 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, dest, &offset);
	SDL_FreeSurface(source);
	SDL_FreeSurface(dest);
}

int		quit_editor(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	TTF_CloseFont(sdl->font);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
	return (0);
}

int		hook_keydown(t_sdl *sdl, t_lst *lst)
{
	clear(lst);
	SDL_FreeSurface(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	TTF_CloseFont(sdl->font);
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_error(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("\n\n");
	}
	sdl->win = SDL_CreateWindow("Doom-Nukem", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, W, H, 0);
	if (!sdl->win)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("\n\n");
	}
	if ((sdl->ren = SDL_GetWindowSurface(sdl->win)) == NULL)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("Surface error.\n");
	}
	if ((sdl->mes = SDL_GetWindowSurface(sdl->win)) == NULL)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("Surface error.\n");
	}
}

void	ft_init(t_sdl *sdl)
{
	sdl->running = 1;
	ft_error(sdl);
	sdl->k.state = SDL_GetKeyboardState(NULL);
	if (TTF_Init() == -1)
	{
		ft_putstr(SDL_GetError());
		ft_putstr("TTF Error.\n");
		exit(0);
	}
	sdl->font = TTF_OpenFont("./font/tf2build.ttf", 31);
	if (!sdl->font)
		exit(0);
	sdl->fc.r = 0xFF;
	sdl->fc.g = 0xA5;
	sdl->fc.b = 0x00;
	sdl->fc.a = 0xFF;
}
