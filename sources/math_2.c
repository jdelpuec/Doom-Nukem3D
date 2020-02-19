/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:21:42 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/19 16:09:12 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float		minf(float a, float b)
{
	return (a < b ? a : b);
}

float		maxf(float a, float b)
{
	return (a > b ? a : b);
}

t_vector_2d	vec2_sub(t_vector_2d a, t_vector_2d b)
{
	t_vector_2d ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return (ret);
}

float		get_dot_poduct(t_vector_3d v1, t_vector_3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}
