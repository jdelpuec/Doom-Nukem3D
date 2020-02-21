/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:47 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/21 11:25:27 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	handle_mouse_event(t_win *w, t_ray *r)
{
	(void)w;
	(void)r;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	// handle_mouse_mvt(w, r);
}
