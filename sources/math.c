/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 10:51:22 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/20 17:55:18 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

t_vector_3d	get_normal_wall(t_vector_2d v1, t_vector_2d v2)
{
	t_vector_3d	norm;
	float		len;

	norm.x = (v2.y - v1.y);
	norm.y = -(v2.x - v1.x);
	len = sqrtf(norm.x * norm.x + norm.y * norm.y);
	if (len == 0)
		return ((t_vector_3d){0, 0, 0});
	norm.x = norm.x / len;
	norm.y = norm.y / len;
	return (norm);
}

float		get_dir_angle(t_ray *r)
{
	float ret;

	ret = 360 / 6.3;
	return (r->player.angle * ret);
}

t_vector_3d	get_cross_poduct(t_vector_3d v1, t_vector_3d v2)
{
	t_vector_3d ret;

	ret.x = (v1.y * v2.z - v1.z * v2.y);
	ret.y = (v1.z * v2.x - v1.x * v2.z);
	ret.z = (v1.x * v2.y - v1.y * v2.x);
	return (ret);
}

float		get_vector2d_length(t_vector_2d v)
{
	return (sqrtf(v.x * v.x + v.y * v.y));
}

t_vector_3d	normalize_vec(t_vector_3d v)
{
	float	len;

	len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}
