/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:47 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/19 15:30:50 by lubernar         ###   ########.fr       */
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
