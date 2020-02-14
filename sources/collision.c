/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:29:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/14 13:39:39 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"
#include "event.h"

void    wall_collision_2(t_ray *r, t_wall wall)
{
	t_vector_3d	normal;
	t_vector_3d	tmp;

	tmp = r->player.velocity;
	normal = get_normal_wall(wall.p1, wall.p2);
	r->player.velocity.x = tmp.x - get_dot_poduct(normal, tmp) * normal.x;
	r->player.velocity.y = tmp.y - get_dot_poduct(normal, tmp) * normal.y;
}

void    wall_collision(t_ray *r, t_vector_3d wd, t_wall wall)
{
	t_vector_3d	old;
	(void)wall;
	old 	= r->player.velocity;
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
