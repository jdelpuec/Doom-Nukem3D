/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:15:57 by ebonafi           #+#    #+#             */
/*   Updated: 2019/11/26 11:51:20 by jdelpuec         ###   ########.fr       */
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

void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k)
{
	float ms;

	ms = (float)10 / FPS; // temp value

	(void)w;
	(void)r;
	(void)k;

	// if (k->state[SDL_SCANCODE_W] == 1)
	// {
	// 	if (map[(int)r->pos_y][(int)(r->pos_x + (r->dir_x * ms))] == 0)
	// 		r->pos_x += r->dir_x * ms;
	// 	if (map[(int)(r->pos_y + (r->dir_y * ms))][(int)(r->pos_x)] == 0)
	// 		r->pos_y += r->dir_y * ms;
	// }
	// if (k->state[SDL_SCANCODE_S] == 1)
	// {
	// 	if (map[(int)(r->pos_y)][(int)(r->pos_x - (r->dir_x * ms))] == 0)
	// 		r->pos_x -= r->dir_x * ms;
	// 	if (map[(int)(r->pos_y - (r->dir_y * ms))][(int)(r->pos_x)] == 0)
	// 		r->pos_y -= r->dir_y * ms;
	// }
	// if (k->state[SDL_SCANCODE_A] == 1)
	// {
	// 	if (map[(int)(r->pos_y)][(int)(r->pos_x - (r->plane_x * ms))] == 0)
	// 		r->pos_x -= r->plane_x * ms;
	// 	if (map[(int)(r->pos_y - (r->plane_y * ms))][(int)(r->pos_x)] == 0)
	// 		r->pos_y -= r->plane_y * ms;
	// }
	// if (k->state[SDL_SCANCODE_D] == 1)
	// {
	// 	if (map[(int)(r->pos_y)][(int)(r->pos_x + (r->plane_x * ms))] == 0)
	// 		r->pos_x += r->plane_x * ms;
	// 	if (map[(int)(r->pos_y + (r->plane_y * ms))][(int)(r->pos_x)] == 0)
	// 		r->pos_y += r->plane_y * ms;
	// }
}

int	handle_keyboard_event(t_win *w, t_keyboard *k)
{
	int	ret;

	ret = handle_keyboard_misc(w, k);
	return (ret);
}
