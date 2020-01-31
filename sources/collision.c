/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:29:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/01/31 17:33:29 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"

// void    wall_direction_2(t_ray *r, t_vector_2d p1, t_vector_2d p2, float ms)
// {
// 	float	del_x;
// 	float	del_y;

// 	del_x	= fabsf(p2.x - p1.x);
// 	del_y	= fabsf(p2.y - p1.y);
//     if (del_y - del_x > 0)
//     {
        
//     }
// }

void    wall_direction(t_ray *r, t_vector_2d p1, t_vector_2d p2, float ms)
{
	float	del_x;
	float	del_y;

	del_x	= p2.x - p1.x;
	del_y	= p2.y - p1.y;
	if (del_x == 0)
	{
        r->player.velocity.x = del_y * (r->player.velocity.x * ms * del_x +
		r->player.velocity.y * ms * del_y) / (del_x * del_x + del_y + del_y) * 0.8;
		r->player.velocity.x = del_x * (r->player.velocity.x * ms * del_x +
		r->player.velocity.y * ms * del_y) / (del_x * del_x + del_y + del_y) * 0.8;
        return ;
	}
    else if (del_y == 0)
	{
		r->player.velocity.y = del_x * (r->player.velocity.x * ms * del_x +
		r->player.velocity.y * ms * del_y) / (del_x * del_x + del_y + del_y) * 0.8;
		r->player.velocity.y = del_y * (r->player.velocity.x * ms * del_x +
		r->player.velocity.y * ms * del_y) / (del_x * del_x + del_y + del_y) * 0.8;
        return ;
	}
	
    // wall_direction_2(r, p1, p2, ms);
    return ;
}