/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:02:38 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/10 15:41:52 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct		s_ray
{
	int			x;
	int			y;
	int			i;
	int			sector_count;
	int			cur_sector;
	int			last_sec;
	float		dist_pp;
	float		ray_angle;

	t_player	player;
	t_wall		old_wall;
	t_sector	*sectors;
	t_vector_2d	ray_end;	

	float		s02_x;
	float		s02_y;
	float		s10_x;
	float		s10_y;
	float		s32_x;
	float		s32_y;
	float		s_denom;
	float		t_denom;
	float		denom;
	float		denom_is_pos;
	float		t;

	float		hit_x;
	float		hit_y;
	float		light;
	float		dist;
	float		dist_wall;
	float		offset_start;
	float		offset_end;
	float		line_h;
	int			y_min;
	int			y_max;

	float		thresh;
	float		speed;
	float		tmp;
	float		dir_angle;
	int			direction;


	int		x_1;
	int		y_1;
	int		x_2;
	int		y_2;
}					t_ray;
float				deg_to_rad(float angle);

#endif
