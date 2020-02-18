/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:11:22 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/17 13:22:06 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	pixel(t_win *sdl, int x, int y)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	*((int *)sdl->surface->pixels + (y * WIN_W + x)) = sdl->color;
}

void	print_messages(t_win *sdl)
{
	int		cy;
	int		cx;
	char	**s;

	s = malloc(sizeof(char**));
	s[0] = "Bonjour ninja, apres votre combat vous etes epuise et avez besoin"
	"de vous remettre en forme, trouvez des";
	s[1] = "bolles de nouilles et des baguettes afin de pouvoir les manger.";
	cy = 10;
	sdl->color = 0x000000;
	while (cy != WIN_H / 10)
	{
		cx = 10;
		while (++cx <= (WIN_W) - 10)
			pixel(sdl, cx, cy);
		cy++;
	}
	sdl->mes = TTF_RenderText_Solid(sdl->font2, s[0], sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface(15, 15, sdl->mes, sdl->surface);
	sdl->mes = TTF_RenderText_Solid(sdl->font2, s[1], sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface(15, 40, sdl->mes, sdl->surface);
}
