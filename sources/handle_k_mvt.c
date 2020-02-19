/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_k_mvt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:41:55 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/19 15:18:57 by lubernar         ###   ########.fr       */
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

void	check_walls(t_ray *r, t_vector_3d new_pos, t_wall wall)
{
		if (test_box(r, new_pos, wall) == 1)
			{
				if ((r->tmp = fabsf(check_line_point(wall.p1, wall.p2, new_pos))
																		< 10))
				{
					if (wall.portal_sector >= 0 && r->player.position.z >
					 	r->sectors[wall.portal_sector].floor_height
						+ (PLAY_H >> 1) && r->player.position.z
						<= r->sectors[wall.portal_sector].ceil_height)
					{
						r->player.sector = wall.portal_sector;
						r->speed = 5.0;
						r->player.velocity.x = 0;
						return ;
					}
					else if (r->tmp < r->space)
					{
						r->player.velocity.x = 0.0;
						r->player.velocity.y = 0.0;
						return ;					
					}
					else
					{
						new_pos = (t_vector_3d) {wall.p2.x - wall.p1.x
						, wall.p2.y - wall.p1.y, 0};
						wall_collision(r, new_pos, wall);
					}
				}
			}
}

void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k)
{
	int			i;
	float		ms;
	t_vector_3d	new_pos;
	t_wall		wall;

	w->fps = w->fps == 0 ? 1 : w->fps;
	ms	= (1.0 / w->fps);
	i	= 0;
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
	if (r->player.velocity.x != 0 || r->player.velocity.y != 0)
	{
		while (i < r->sectors[r->player.sector].wall_count)
		{
			new_pos = (t_vector_3d) {r->player.position.x
						+ r->player.velocity.x, r->player.position.y
						+ r->player.velocity.y, 0};
			wall = r->sectors[r->player.sector].walls[i];
			if (test_box(r, new_pos, wall) == 1)
			{
				if ((r->tmp = fabsf(check_line_point(wall.p1, wall.p2, new_pos))
																		< 10))
				{
					if (wall.portal_sector >= 0 && r->player.position.z >
					 	r->sectors[wall.portal_sector].floor_height
						+ (PLAY_H >> 1) && r->player.position.z
						<= r->sectors[wall.portal_sector].ceil_height)
					{
						r->player.sector = wall.portal_sector;
						r->speed = 5.0;
						r->player.velocity.x = 0;
						break;
					}
					else if (r->tmp < r->space)
					{
						r->player.velocity.x = 0.0;
						r->player.velocity.y = 0.0;
						break;					
					}
					else
					{
						new_pos = (t_vector_3d) {wall.p2.x - wall.p1.x
						, wall.p2.y - wall.p1.y, 0};
						wall_collision(r, new_pos, wall);
					}
				}
			}
			i++;
		}
		r->player.position.x += r->player.velocity.x;
		r->player.position.y += r->player.velocity.y;
	}
	r->player.velocity.x = 0.0;
	r->player.velocity.y = 0.0;
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