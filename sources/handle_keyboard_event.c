/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:15:57 by ebonafi           #+#    #+#             */
/*   Updated: 2020/01/13 18:00:48 by jdelpuec         ###   ########.fr       */
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
	if (k->state[SDL_SCANCODE_LCTRL] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_LGUI] == 1)
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

void	inter_box()
{
	
}

void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k)
{
	int			i;
	float		ms;
	t_vector_2d	new_pos;

	ms	= (float)(1.0 / w->fps); // temp value
	i	= 0;

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

	r->player.velocity.x -= r->player.velocity.x * 6.0f * ms;
    r->player.velocity.y -= r->player.velocity.y * 6.0f * ms;

	if (r->player.velocity.x > 1.0 || r->player.velocity.x < 1.0 || r->player.velocity.y > 1.0 || r->player.velocity.y < 1.0)
	{
		while (i < r->sectors[r->player.sector].wall_count)
		{
			new_pos = (t_vector_2d) {r->player.position.x + r->player.velocity.x * ms,
						 r->player.position.y + r->player.velocity.y * ms};
			if (inter_box())
		}
		r->player.position.x += r->player.velocity.x * ms;
		r->player.position.y += r->player.velocity.y * ms;
	}
	else
	{
		r->player.velocity.x = 0.0;
		r->player.velocity.y = 0.0;
	}
}

int	handle_keyboard_event(t_win *w, t_keyboard *k)
{
	int	ret;

	ret = handle_keyboard_misc(w, k);
	return (ret);
}
