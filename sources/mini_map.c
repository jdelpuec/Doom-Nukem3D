/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:19:48 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/04 14:27:42 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "mini_map.h"
#include "raycasting.h"

void	draw_point(t_win *w, int x, int y, int c)
{
    if(x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		*((int *)w->surface->pixels + (y * WIN_W + x)) = c;
}

void	draw_line(t_win *w, t_ray *r)
{
	t_mini_map  m;
	int		    tmp;
	int		    y_longer;

	y_longer = 0;
	m.x_delta = r->x_2 - r->x_1;
	m.y_delta = r->y_2 - r->y_1;
	if (abs(m.y_delta) > abs(m.x_delta))
	{
		tmp = m.x_delta;
		m.x_delta = m.y_delta;
		m.y_delta = tmp;
		y_longer = 1;
	}
	m.end_val = m.x_delta;
	if (m.x_delta < 0)
	{
		m.incr = -1;
		m.x_delta = -m.x_delta;
	}
	else
		m.incr = 1;

	if (m.x_delta == 0)
		m.decr = (double)m.y_delta;
	else
		m.decr = (double)m.x_delta / (double)m.y_delta;

	m.j = 0.0;
	m.i = 0;
	if (y_longer == 1)
		while (m.i != m.end_val)
		{
			draw_point(w, (r->x_1 + (int)m.j), (r->y_1 + m.i), 0xff0000);
			m.j += m.decr;
			m.i += m.incr;
		}
	else
		while (m.i != m.end_val)
		{
			draw_point(w, (r->x_1 + m.i), (r->y_1 + (int)m.j), 0xff0000);
			m.j += m.decr;
			m.i += m.incr;
		}
}

void	draw_minimap(t_win *w, t_ray *r)
{
	int i;
	int j;

	draw_point(w, (10 + ((int)r->player.position.x << 2)), (10 + ((int)r->player.position.y << 2)), 0x00ff00);
	i = 0;
	while (i < r->sector_count)
	{
		j = 0;
		while (j < r->sectors[i].wall_count)
		{
			r->x_1 = 10 + ((int)r->sectors[i].walls[j].p1.x << 2);
			r->y_1 = 10 + ((int)r->sectors[i].walls[j].p1.y << 2);
			r->x_2 = 10 + ((int)r->sectors[i].walls[j].p2.x << 2);
			r->y_2 = 10 + ((int)r->sectors[i].walls[j].p2.y << 2);
			draw_line(w, r);
			j++;
		}
		i++;
	}
	j = 0;
	while (j < r->sectors[r->player.sector].wall_count)
	{
		r->x_1 = 10 + ((int)r->sectors[r->player.sector].walls[j].p1.x << 2);
		r->y_1 = 10 + ((int)r->sectors[r->player.sector].walls[j].p1.y << 2);
		r->x_2 = 10 + ((int)r->sectors[r->player.sector].walls[j].p2.x << 2);
		r->y_2 = 10 + ((int)r->sectors[r->player.sector].walls[j].p2.y << 2);
		draw_line(w, r);
		j++;
	}
}