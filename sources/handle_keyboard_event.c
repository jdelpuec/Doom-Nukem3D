/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:15:57 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/21 14:53:40 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "event.h"

int		handle_keyboard_misc(t_win *w, t_keyboard *k)
{
	if (k->state[SDL_SCANCODE_ESCAPE] == 1)
	{
		SDL_DestroyWindow(w->win);
		TTF_CloseFont(w->font);
		SDL_Quit();
		return (-1);
	}
	return (1);
}

int		inter_box(t_ray *r, t_wall wall, t_vector_3d n_pos)
{
	t_vector_3d	pos;
	float		min_p;
	float		max_p;
	float		min_w;
	float		max_w;

	pos = r->player.position;
	min_p = pos.x < n_pos.x ? (pos.x) : (n_pos.x);
	max_w = wall.p1.x > wall.p2.x ? (wall.p1.x) : (wall.p2.x);
	min_w = wall.p1.x < wall.p2.x ? (wall.p1.x) : (wall.p2.x);
	max_p = pos.x > n_pos.x ? (pos.x) : (n_pos.x);
	if (min_p <= max_w && min_w <= max_p)
	{
		min_p = pos.y < n_pos.y ? (pos.y) : (n_pos.y);
		max_w = wall.p1.y > wall.p2.y ? (wall.p1.y) : (wall.p2.y);
		min_w = wall.p1.y < wall.p2.y ? (wall.p1.y) : (wall.p2.y);
		max_p = pos.y > n_pos.y ? (pos.y) : (n_pos.y);
		if (min_p <= max_w && min_w <= max_p)
			return (1);
		return (0);
	}
	else
		return (0);
}

int		test_box(t_ray *r, t_vector_3d p, t_wall wall)
{
	float min_x;
	float max_x;
	float min_y;
	float max_y;

	if (wall.portal_sector != -1)
		return (inter_box(r, wall, p));
	min_x = (wall.p1.x < wall.p2.x) ? (wall.p1.x) : (wall.p2.x);
	max_x = (wall.p1.x >= wall.p2.x) ? (wall.p1.x) : (wall.p2.x);
	min_y = (wall.p1.y < wall.p2.y) ? (wall.p1.y) : (wall.p2.y);
	max_y = (wall.p1.y >= wall.p2.y) ? (wall.p1.y) : (wall.p2.y);
	if ((min_x == max_x) || (min_y == max_y))
	{
		r->tmp = (min_x == max_x) ? 1 : 2;
		if (r->tmp == 1)
			if (p.x > min_x)
				max_x += r->thresh;
			else
				min_x -= r->thresh;
		else
			p.y > min_y ? (max_y += r->thresh) : (min_y -= r->thresh);
	}
	return ((p.x >= min_x && p.x <= max_x) && (p.y >= min_y && p.y <= max_y));
}

float	check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p)
{
	return ((l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x));
}

int		handle_keyboard_event(t_win *w, t_keyboard *k)
{
	int	ret;

	ret = handle_keyboard_misc(w, k);
	return (ret);
}
