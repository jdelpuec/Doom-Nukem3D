/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:29:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/03/05 15:37:43 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "event.h"

void		new_pos_collision(t_vector_3d new_pos, t_wall wall, t_ray *r)
{
	new_pos = (t_vector_3d) {wall.p2.x - wall.p1.x, wall.p2.y - wall.p1.y, 0};
	wall_collision(r, new_pos, wall);
}

int			how_to_break_properly(t_wall wall, t_ray *r, t_vector_3d new_pos)
{
	(void)new_pos;
	if (wall.portal_sector >= 0 && r->player.position.z >
	r->sectors[wall.portal_sector].floor_height + (PLAY_H >> 1)
	&& r->player.position.z
	<= r->sectors[wall.portal_sector].ceil_height)
	{
		r->player.sector = wall.portal_sector;
		r->speed = 5.0;
		r->player.velocity.x = 0;
		return (-1);
	}
	else
	{
		r->player.velocity.x = 0.0;
		r->player.velocity.y = 0.0;
		return (-1);
	}
	return (1);
}

void		check_walls(t_ray *r)
{
	t_vector_3d	new_pos;
	t_wall		wall;
	int			i;

	i = -1;
	while (++i < r->sectors[r->player.sector].wall_count)
	{
		new_pos = (t_vector_3d) {r->player.position.x + r->player.velocity.x,
						r->player.position.y + r->player.velocity.y, 0};
		wall = r->sectors[r->player.sector].walls[i];
		if (test_box(r, new_pos, wall) == 1)
		{
			if ((r->tmp = check_line_point(wall.p2, wall.p1, new_pos)) < 10)
			{
				if (how_to_break_properly(wall, r, new_pos) == -1)
					break ;
			}
		}
	}
}

void		wall_collision_2(t_ray *r, t_wall wall)
{
	t_vector_3d	normal;
	t_vector_3d	tmp;

	tmp = r->player.velocity;
	normal = get_normal_wall(wall.p1, wall.p2);
	r->player.velocity.x = tmp.x - get_dot_poduct(normal, tmp) * normal.x;
	r->player.velocity.y = tmp.y - get_dot_poduct(normal, tmp) * normal.y;
}

void		wall_collision(t_ray *r, t_vector_3d wd, t_wall wall)
{
	t_vector_3d	old;

	old = r->player.velocity;
	if (wd.x == 0)
	{
		r->player.velocity.x = wd.y * (old.x * wd.x +
		old.y * wd.y) / (wd.x * wd.x + wd.y + wd.y);
		r->player.velocity.x = wd.x * (old.x * wd.x +
		old.y * wd.y) / (wd.x * wd.x + wd.y + wd.y);
		return ;
	}
	else if (wd.y == 0)
	{
		r->player.velocity.y = wd.x * (old.x * wd.x +
		old.y * wd.y) / (wd.x * wd.x + wd.y + wd.y);
		r->player.velocity.y = wd.y * (old.x * wd.x +
		old.y * wd.y) / (wd.x * wd.x + wd.y + wd.y);
		return ;
	}
	wall_collision_2(r, wall);
	return ;
}
