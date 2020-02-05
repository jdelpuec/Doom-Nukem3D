/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:29:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/05 16:25:00 by jdelpuec         ###   ########.fr       */
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

void    wall_collision(t_ray *r, t_vector_2d p1, t_vector_2d p2)
{
	float	del_x;
	float	del_y;

	del_x	= p2.x - p1.x;
	del_y	= p2.y - p1.y;
	if (del_x == 0)
	{
        r->player.velocity.x = del_y * (r->player.velocity.x * del_x +
		r->player.velocity.y * del_y) / (del_x * del_x + del_y + del_y);
		r->player.velocity.x = del_x * (r->player.velocity.x * del_x +
		r->player.velocity.y * del_y) / (del_x * del_x + del_y + del_y);
        return ;
	}
    else if (del_y == 0)
	{
		r->player.velocity.y = del_x * (r->player.velocity.x * del_x +
		r->player.velocity.y * del_y) / (del_x * del_x + del_y + del_y);
		r->player.velocity.y = del_y * (r->player.velocity.x * del_x +
		r->player.velocity.y * del_y) / (del_x * del_x + del_y + del_y);
        return ;
	}
    wall_collision_2(r, p1, p2);
    return ;
}