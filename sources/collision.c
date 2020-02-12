/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:29:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/10 10:36:41 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"

void    wall_collision_2(t_ray *r, t_vector_2d p1, t_vector_2d p2)
{
	t_vector_3d	normal;
	t_vector_3d	tmp;
	// float		len;

	tmp = r->player.velocity;
	normal = get_normal_wall(p1, p2);
	// len = get_vector_length(r->player.velocity);
	// tmp = get_cross_poduct(r->player.velocity, normal);
	// r->player.velocity = get_cross_poduct(normal, tmp);
	// r->player.velocity = normalize_vec(r->player.velocity);
	// r->player.velocity.x *= len;
	// r->player.velocity.y *= len;


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
    // wall_collision_2(r, p1, p2);
    return ;
}
