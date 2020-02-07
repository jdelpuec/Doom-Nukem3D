/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:15:57 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/07 18:46:09 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"
#include "event.h"

void	init_keyboard(t_keyboard *k)
{
	k->state = SDL_GetKeyboardState(NULL);
}

int	is_key_pressed(t_keyboard *k)
{
	int	pressed;

	pressed = 0;
	if (k->state[SDL_SCANCODE_W] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_S] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_A] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_D] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_Q] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_E] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_ESCAPE] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_SPACE] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_LGUI] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_R] == 1)
		pressed++;
	return (pressed);
}

int	handle_keyboard_misc(t_win *w, t_keyboard *k)
{
	if (k->state[SDL_SCANCODE_ESCAPE] == 1)
	{
		SDL_DestroyWindow(w->win);
		SDL_Quit();
		return (-1);
	}
	return (1);
}

float		check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p)
{
	// printf("%f  \n", (l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x));
	return ((l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x));
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
			if (p.y > min_y) 
				max_y += r->thresh;
			else
				min_y -= r->thresh;
	}
	return ((p.x >= min_x && p.x <= max_x) && (p.y >= min_y && p.y <= max_y));
}

void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k)
{
	int			i;
	float		ms;
	t_vector_3d	new_pos;
	t_wall		wall;

	w->fps = w->fps == 0 ? 1 : w->fps;
	ms	= (1.0 / w->fps); 	// Reverse FPS --> make moovement smooth even tho the program et slow.
	i	= 0;

	// printf("%f \n", ms);

	if (r->player.sector > 8 || r->player.sector == 0)
		r->speed = k->state[SDL_SCANCODE_LSHIFT] == 1 ? 8.0 : 5.0;

	if (k->state[SDL_SCANCODE_R] == 1)
	{
		r->player.position.x		= 0.0;
		r->player.position.y		= 0.0;
		r->player.position.z		= 0.0;			/// RESET position.
		r->player.angle				= 0.0;
		r->player.sector			= 0;
	}
	if (k->state[SDL_SCANCODE_A] == 1)
		r->player.angle -= 2.5 * ms;
		// r->player.angle -= 0.01;		
	if (k->state[SDL_SCANCODE_D] == 1)
		r->player.angle += 2.5 * ms;
		// r->player.angle += 0.01;
	if (fabsf(r->player.angle) >= 6.299992)
		r->player.angle = 0;

	r->dir_angle = get_dir_angle(r);

	if (k->state[SDL_SCANCODE_W] == 1)
	{
		r->player.velocity.x = r->speed * cosf(r->player.angle) * ms;
		r->player.velocity.y = r->speed * -sinf(r->player.angle) * ms;
	}
	if (k->state[SDL_SCANCODE_S] == 1)
	{
		r->player.velocity.x = r->speed * -cosf(r->player.angle) * ms;
		r->player.velocity.y = r->speed * sinf(r->player.angle) * ms;
	}
		
	if (k->state[SDL_SCANCODE_Q] == 1)
	{
		r->player.velocity.x += r->speed * sinf(r->player.angle) * ms;
		r->player.velocity.y += r->speed * cosf(r->player.angle) * ms;
	}
	if (k->state[SDL_SCANCODE_E] == 1)
	{
		r->player.velocity.x -= r->speed * sinf(r->player.angle) * ms;
		r->player.velocity.y -= r->speed * cosf(r->player.angle) * ms;
	}

	if (k->state[SDL_SCANCODE_SPACE] == 1)
		r->player.velocity.z = 60.0;
	

///////////////				CHECK LES COLLISIONS AVEC TETE DANS LE PLAFOND (sector changes ??) ///////////////////


	// printf("x = %f; y = %f ; z = %f  \n", r->player.velocity.x, r->player.velocity.y, r->player.position.z);
	if (ms > 0.1)
	{
		r->player.velocity.x = 0;
		r->player.velocity.y = 0;
	}
	if (r->player.velocity.x != 0|| r->player.velocity.y != 0)
	{
		while (i < r->sectors[r->player.sector].wall_count)
		{
			new_pos = (t_vector_3d) {r->player.position.x + r->player.velocity.x,
						 r->player.position.y + r->player.velocity.y, 0};
			wall	= r->sectors[r->player.sector].walls[i];
			if (test_box(r, new_pos, wall) == 1)
			{
				if (((r->tmp = fabsf(check_line_point(wall.p1, wall.p2, new_pos))) < 10))
				{
					if (wall.portal_sector >= 0 && (r->player.position.z + PLAYER_H >
					 r->sectors[wall.portal_sector].floor_height &&
					 r->player.position.z <= r->sectors[wall.portal_sector].ceil_height))
					{
						r->player.sector		= wall.portal_sector;
						r->speed				= 5.0;
						r->player.velocity.x	= 0;
						break;
					}
					else
					{
						new_pos = (t_vector_3d) {wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y, 0};
						wall_collision(r, new_pos);
					}
				}
			}
			i++;
		}
		// if ((fabsf(new_pos.y) >= fabsf(wall.p1.y) - 0.5 || fabsf(new_pos.y) >= fabsf(wall.p2.y) - 0.5))
		// 	r->player.velocity.x = 0;
		// if ((fabsf(new_pos.x) >= fabsf(wall.p1.x) - 0.5 || fabsf(new_pos.x) >= fabsf(wall.p2.x) - 0.5))
		// 	r->player.velocity.y = 0;
		r->player.position.x += r->player.velocity.x;
		r->player.position.y += r->player.velocity.y;
	}
	r->player.velocity.x = 0.0;
	r->player.velocity.y = 0.0;
	if (k->state[SDL_SCANCODE_LCTRL] != 1)
	{
		if (r->player.position.z + r->player.velocity.z * ms < r->sectors[r->player.sector].ceil_height)
			r->player.position.z += r->player.velocity.z * ms;
		else
			r->player.position.z = r->sectors[r->player.sector].ceil_height;

		if (r->player.position.z < r->sectors[r->player.sector].floor_height + PLAYER_H)
		{
			r->player.position.z = r->sectors[r->player.sector].floor_height + PLAYER_H;
			r->player.velocity.z = 0.0;
		}
		else
			r->player.velocity.z -= 2.0;
	}
}

int	handle_keyboard_event(t_win *w, t_keyboard *k)
{
	int	ret;

	ret = handle_keyboard_misc(w, k);
	return (ret);
}
