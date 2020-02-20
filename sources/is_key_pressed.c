/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key_pressed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:57:44 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/20 18:09:31 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "event.h"

void	init_keyboard(t_keyboard *k)
{
	k->state = SDL_GetKeyboardState(NULL);
}

int		is_key_pressed2(t_keyboard *k, int pressed)
{
	if (k->state[SDL_SCANCODE_LGUI] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_T] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_R] == 1)
		pressed++;
	if (k->state[SDL_SCANCODE_O] == 1)
		pressed++;
	return (pressed);
}

int		is_key_pressed(t_keyboard *k)
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
	pressed = is_key_pressed2(k, pressed);
	return (pressed);
}
