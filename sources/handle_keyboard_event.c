/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:15:57 by ebonafi           #+#    #+#             */
/*   Updated: 2020/01/22 16:22:23 by jdelpuec         ###   ########.fr       */
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
	if (k->state[SDL_SCANCODE_ESCAPE] == 1)
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

float		check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_2d p)
{
	printf("dist_wall = %f \n", (l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x));
	return ((l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x));
}

int		inter_box(t_ray *r, t_wall wall, float x1, float y1)
{
	float	x0;
	float	y0;
	float	tmp;
	float	tmp2;

	x0 = r->player.position.x;
	y0 = r->player.position.y;

	tmp		= (((x0) < (x1)) ? (x0) : (x1));
	tmp2	= (((wall.p1.x) > (wall.p2.x)) ? (wall.p1.x) : (wall.p2.x));
	if (tmp > tmp2)
		return (0);
	tmp		= (((wall.p1.x) < (wall.p2.x)) ? (wall.p1.x) : (wall.p2.x));
	tmp2	= (((x0) > (x1)) ? (x0) : (x1));
	if (tmp > tmp2)
		return (0);
	tmp		= (((y0) < (y1)) ? (y0) : (y1));
	tmp2	= (((wall.p1.y) > (wall.p2.y)) ? (wall.p1.y) : (wall.p2.y));
	if (tmp > tmp2)
		return(0);
	tmp		= (((wall.p1.y) < (wall.p2.y)) ? (wall.p1.y) : (wall.p2.y));
	tmp2	= (((y0) > (y1)) ? (y0) : (y1));
	if (tmp > tmp2)
		return (0);
	return (1);
}

// int		inter_box2(t_ray *r, t_wall wall)
// {
	
// }

void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k)
{
	int			i;
	float		ms;
	t_vector_2d	new_pos;
	t_wall		wall;

	ms	= (1.0 / w->fps); // temp value to be limited
	i	= 0;

	// printf("%f \n", ms);
	if (k->state[SDL_SCANCODE_R] == 1)
	{
		r->player.position.x		= 0.0;
		r->player.position.y		= 0.0;
		r->player.position.z		= 0.0;
		r->player.angle				= 0.0;
		r->player.sector			= 0.0;
	}

	if (k->state[SDL_SCANCODE_W] == 1)
	{
		r->player.velocity.x = cos(r->player.angle) * 10.0;
		r->player.velocity.y = sin(r->player.angle) * 10.0;
	}
	if (k->state[SDL_SCANCODE_S] == 1)
	{
		r->player.velocity.x = -cos(r->player.angle) * 10.0;
		r->player.velocity.y = -sin(r->player.angle) * 10.0;
	}
	if (k->state[SDL_SCANCODE_A] == 1)
		r->player.angle -= 1.6f * ms;
	if (k->state[SDL_SCANCODE_D] == 1)
		r->player.angle += 1.6f * ms;
	if (k->state[SDL_SCANCODE_SPACE] == 1)
		r->player.velocity.z = 60.0;

	if (ms > 0.1)
	{
		r->player.velocity.x = 0;
		r->player.velocity.y = 0;
	}
	if (r->player.velocity.x > 1.0 || r->player.velocity.x < 1.0 || r->player.velocity.y > 1.0 || r->player.velocity.y < 1.0)
	{
    	r->player.velocity.y -= r->player.velocity.y * 6.0f * ms;
		r->player.velocity.x -= r->player.velocity.x * 6.0f * ms;
		while (i < r->sectors[r->player.sector].wall_count)
		{
			new_pos = (t_vector_2d) {r->player.position.x + r->player.velocity.x * ms,
						 r->player.position.y + r->player.velocity.y * ms};
			wall	= r->sectors[r->player.sector].walls[i];
				if (check_line_point(wall.p1, wall.p2, new_pos) > -1.5)
				{
					if (wall.portal_sector >= 0)
					{
						r->player.sector		= wall.portal_sector;
						break;
					}
					else
					{
						new_pos = (t_vector_2d) {wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y};
						r->player.velocity.x = new_pos.x * (r->player.velocity.x * ms * new_pos.x + r->player.velocity.y * ms * new_pos.y) /  (new_pos.x * new_pos.x + new_pos.y + new_pos.y);
						r->player.velocity.x = new_pos.y * (r->player.velocity.x * ms * new_pos.x + r->player.velocity.y * ms * new_pos.y) / (new_pos.x * new_pos.x + new_pos.y + new_pos.y);
					}
				}
			i++;
		}
		r->player.position.x += r->player.velocity.x * ms;
		r->player.position.y += r->player.velocity.y * ms;
	}
	r->player.velocity.x = 0.0;
	r->player.velocity.y = 0.0;
	if (k->state[SDL_SCANCODE_LCTRL] != 1)
	{
		r->player.position.z += r->player.velocity.z * ms;
		if (r->player.position.z < r->sectors[r->player.sector].floor_height + PLAYER_H)
		{
			r->player.position.z = r->sectors[r->player.sector].floor_height + PLAYER_H;
			r->player.velocity.z = 0.0;
		}
		else
			r->player.velocity.z -= 300.0 * ms;
	}
}

int	handle_keyboard_event(t_win *w, t_keyboard *k)
{
	int	ret;

	ret = handle_keyboard_misc(w, k);
	return (ret);
}
