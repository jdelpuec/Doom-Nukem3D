/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 09:55:59 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/17 12:09:47 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"
#include "../includes/list.h"

void	draw_contour(t_sdl *sdl)
{
	sdl->color = GRAY;
	sdl->cx = 0;
	while (sdl->cx != W)
	{
		sdl->cy = 0;
		while (sdl->cy != H)
		{
			pixel(sdl, sdl->cx, sdl->cy);
			sdl->cy++;
		}
		sdl->cx++;
	}
}

void	draw_grid(t_sdl *sdl)
{
	sdl->color = GRAY;
	sdl->cy = 10;
	while (sdl->cy <= H - 10)
	{
		sdl->cx = 10;
		while (sdl->cx <= W / 1.5)
		{
			pixel(sdl, sdl->cx, sdl->cy);
			sdl->cx++;
		}
		sdl->cy += 20;
	}
	sdl->cx = 10;
	while (sdl->cx <= W / 1.5)
	{
		sdl->cy = 10;
		while (sdl->cy <= H - 10)
		{
			pixel(sdl, sdl->cx, sdl->cy);
			sdl->cy++;
		}
		sdl->cx += 20;
	}
}

void	draw_menu(t_sdl *sdl)
{
	draw_contour(sdl);
	sdl->color = BLACK;
	sdl->cy = 10;
	while (sdl->cy != H - 10)
	{
		sdl->cx = 10;
		while (++sdl->cx <= (W / 1.5) - 10)
			pixel(sdl, sdl->cx, sdl->cy);
		sdl->cy++;
	}
	sdl->color = DARK_GRAY;
	sdl->cy = 10;
	while (sdl->cy != H - 10)
	{
		sdl->cx = (W / 1.5) + 10;
		while (sdl->cx <= W - 10)
		{
			pixel(sdl, sdl->cx, sdl->cy);
			sdl->cx++;
		}
		sdl->cy++;
	}
	draw_grid(sdl);
}

void	draw_redsquare(t_sdl *sdl, int x, int y)
{
	int i;
	int j;

	sdl->color = RED;
	j = y;
	while (j != y + 30)
	{
		i = x;
		if (i == x || i == x + 29 || j == y || j == y + 29)
		{
			while (i != x + 30)
			{
				if (j == y || j == y + 29 || i == x || i == x + 29)
				{
					pixel(sdl, i, j);
				}
				i++;
			}
		}
		j++;
	}
}
