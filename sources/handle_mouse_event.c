/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:47 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/01/06 16:38:27 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"

void	handle_mouse_mvt(t_win *w, t_ray *r)
{
	float	rota;
	float	tmp;

	// if (w->e.motion.yrel < 0 && r->coef < 52)
	// 	r->player_h += 20;
	// if (w->e.motion.yrel > 0 && r->coef > -42)
	// 	r->player_h -= 20;
		
	if (w->e.motion.xrel < 0)
	{
		rota = -0.04;
		tmp = r->dir_x;
		r->dir_x = r->dir_x * cos(-rota) - r->dir_y * sin(-rota);
		r->dir_y = tmp * sin(-rota) + r->dir_y * cos(-rota);
		tmp = r->plane_x;
		r->plane_x = r->plane_x * cos(-rota) - r->plane_y * sin(-rota);
		r->plane_y = tmp * sin(-rota) + r->plane_y * cos(-rota);
	}
	if (w->e.motion.xrel > 0)
	{
		rota = 0.04;
		tmp = r->dir_x;
		r->dir_x = r->dir_x * cos(-rota) - r->dir_y * sin(-rota);
		r->dir_y = tmp * sin(-rota) + r->dir_y * cos(-rota);
		tmp = r->plane_x;
		r->plane_x = r->plane_x * cos(-rota) - r->plane_y * sin(-rota);
		r->plane_y = tmp * sin(-rota) + r->plane_y * cos(-rota);
	}
}

void	handle_mouse_event(t_win *w, t_ray *r)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	handle_mouse_mvt(w, r);
}
