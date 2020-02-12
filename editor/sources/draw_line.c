/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:15:36 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/05 11:06:08 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"
#include "../includes/list.h"

int		horizontal_line(int error, t_line *line, t_sdl *sdl)
{
	error = line->dx / 2;
	while (line->x != line->x2)
	{
		line->x += line->xinc;
		error += line->dy;
		if (error >= line->dx)
		{
			error -= line->dx;
			line->y += line->yinc;
		}
		pixel(sdl, line->x, line->y);
	}
	return (error);
}

int		vertical_line(int error, t_line *line, t_sdl *sdl)
{
	error = line->dy / 2;
	while (line->y != line->y2)
	{
		line->y += line->yinc;
		error += line->dx;
		if (error >= line->dy)
		{
			error -= line->dy;
			line->x += line->xinc;
		}
		pixel(sdl, line->x, line->y);
	}
	return (error);
}

void	draw_line(t_line *line, t_sdl *sdl)
{
	int		error;

	error = 0;
	line->x = line->x1;
	line->y = line->y1;
	line->dx = line->x2 - line->x1;
	line->dy = line->y2 - line->y1;
	line->xinc = (line->dx > 0) ? 1 : -1;
	line->yinc = (line->dy > 0) ? 1 : -1;
	line->dx = ft_abs(line->dx);
	line->dy = ft_abs(line->dy);
	if (line->dx > line->dy)
		error = horizontal_line(error, line, sdl);
	else
		error = vertical_line(error, line, sdl);
}

void	draw_line_on_click(t_line *line, t_sdl *sdl, t_editor *edit)
{
	sdl->color = RED;
	line->x1 = edit->x1_replace;
	line->y1 = edit->y1_replace;
	line->x2 = sdl->xmouse;
	line->y2 = sdl->ymouse;
	draw_line(line, sdl);
}
