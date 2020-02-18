/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 09:55:59 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/18 14:24:02 by lubernar         ###   ########.fr       */
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

void	draw_menu(t_sdl *sdl, t_editor *edit)
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
	write_text(sdl, edit);
}

void	draw_redsquare(t_sdl *sdl, int x, int y, t_vector_2d *vec)
{
	int i;
	int j;

	sdl->color = RED;
	j = y;
	while (j != y + vec->y)
	{
		i = x;
		if (i == x || i == x + vec->x || j == y || j == y + vec->x)
		{
			while (i != x + vec->y)
			{
				if (j == y || j == y + vec->x || i == x || i == x + vec->x)
				{
					pixel(sdl, i, j);
				}
				i++;
			}
		}
		j++;
	}
}
