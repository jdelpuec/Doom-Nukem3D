/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:47 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/21 15:04:46 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void	handle_mouse_event(t_win *w, t_ray *r)
{
	(void)w;
	(void)r;
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void	mouse_button_down(t_win *w, t_ray *r)
{
	if (w->e.type == SDL_MOUSEMOTION)
		handle_mouse_event(w, r);
	if (w->e.type == SDL_MOUSEBUTTONDOWN && w->fired == 0
												&& r->inv.nb_bullet > 0)
	{
		FMOD_System_PlaySound(w->s.fmod, FMOD_CHANNEL_FREE,
													w->s.shot, 0, NULL);
		w->fired = 1;
		r->inv.nb_bullet--;
		w->old_t_f = SDL_GetTicks();
	}
}
