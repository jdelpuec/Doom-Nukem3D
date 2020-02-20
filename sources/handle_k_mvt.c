/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_k_mvt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:41:55 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/20 17:49:07 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "event.h"

void	reload_restart_straf(t_ray *r, t_keyboard *k, t_win *w, float ms)
{
	if (r->player.sector > 8 || r->player.sector == 0)
		r->speed = k->state[SDL_SCANCODE_LSHIFT] == 1 ? 8.0 : 5.0;
	if (r->player.position.z - PLAY_H != r->sectors[r->cur_sector].floor_height)
		r->speed = 5.0;
	if (k->state[SDL_SCANCODE_R] == 1 && w->reload == 0)
	{
		w->fired = 2;
		w->reload = 1;
		w->old_t = SDL_GetTicks();
		r->inv.nb_bullet += 10;
		FMOD_System_PlaySound(w->s.fmod, FMOD_CHANNEL_FREE, w->s.reload
		, 0, NULL);
	}
	if (k->state[SDL_SCANCODE_T] == 1)
	{
		r->player.position.x = 0.0;
		r->player.position.y = 0.0;
		r->player.position.z = 0.0;
		r->player.angle = 0.0;
		r->player.sector = 0;
	}
	if (k->state[SDL_SCANCODE_A] == 1)
		r->player.angle -= 2.5 * ms;
	if (k->state[SDL_SCANCODE_D] == 1)
		r->player.angle += 2.5 * ms;
}

void	basic_mvt(t_keyboard *k, t_ray *r, float ms)
{
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
}

void	l_ctrl(t_keyboard *k, t_ray *r, float ms)
{
	if (k->state[SDL_SCANCODE_LCTRL] != 1)
	{
		if (r->player.position.z + r->player.velocity.z * ms
		< r->sectors[r->player.sector].ceil_height)
			r->player.position.z += r->player.velocity.z * ms;
		else
			r->player.position.z = r->sectors[r->player.sector].ceil_height;
		if (r->player.position.z < r->sectors[r->player.sector].floor_height
																	+ PLAY_H)
		{
			r->player.position.z = r->sectors[r->player.sector].floor_height
																	+ PLAY_H;
			r->player.velocity.z = 0.0;
		}
		else
			r->player.velocity.z -= r->gravity;
	}
}

void	DEBROUILLE_TOI_AVEC_LE_NOM_DE_CELLE_LA_JU(t_ray *r)
{
	t_wall		wall;
	t_vector_3d	new_pos;
	int			i;

	i = 0;
	if (r->player.velocity.x != 0 || r->player.velocity.y != 0)
	{
		while (i < r->sectors[r->player.sector].wall_count)
		{
			new_pos = (t_vector_3d) {r->player.position.x
						+ r->player.velocity.x, r->player.position.y
						+ r->player.velocity.y, 0};
			wall = r->sectors[r->player.sector].walls[i];
			if (check_walls(r, new_pos, wall) == -1)
				break ;
			i++;
		}
		r->player.position.x += r->player.velocity.x;
		r->player.position.y += r->player.velocity.y;
	}
}

void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k)
{
	float		ms;

	w->fps = w->fps == 0 ? 1 : w->fps;
	ms = (1.0 / w->fps);
	reload_restart_straf(r, k, w, ms);
	if (fabsf(r->player.angle) >= 6.299992)
		r->player.angle = 0;
	r->dir_angle = get_dir_angle(r);
	basic_mvt(k, r, ms);
	if (ms > 0.1)
	{
		r->player.velocity.x = 0;
		r->player.velocity.y = 0;
	}
	DEBROUILLE_TOI_AVEC_LE_NOM_DE_CELLE_LA_JU(r);
	l_ctrl(k, r, ms);
}
