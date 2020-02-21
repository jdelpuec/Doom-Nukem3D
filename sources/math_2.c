/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:21:42 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/21 10:46:09 by cduverge         ###   ########.fr       */
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
