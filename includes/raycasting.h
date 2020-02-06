/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:02:38 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/06 16:14:41 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct		s_ray
{
	int			x;
	int			y;
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
	float		t;


	float		light;
	float		dist;
	float		dist_wall;
	float		offset_start;
	float		offset_end;
	float		line_h;
	int			y_min;
	int			y_max;

	float		speed;
	float		tmp;
	float		dir_angle;
	int			direction;


	int		x_1;
	int		y_1;
	int		x_2;
	int		y_2;

	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				height_wall;
	int				mid_screen;
	int				is_crouch;
	float			player_h;
	float			pos_x;
	float			pos_y;
	float			camera_x;
	float			dir_x;
	float			dir_y;
	float			delta_y;
	float			delta_x;
	float			side_dist_y;
	float			side_dist_x;
	float			ray_dir_x;
	float			ray_dir_y;
	float			plane_x;
	float			plane_y;
	float			coef;
}					t_ray;

void		init_raycasting(t_ray *r);
void		wall_collision(t_ray *r, t_vector_3d wd);
float		get_dir_angle(t_ray *r);
float		get_dot_poduct(t_vector_3d v1, t_vector_3d v2);
float		get_vector_length(t_vector_3d v);
t_vector_3d	normalize_vec(t_vector_3d v);
t_vector_3d	get_normal_wall(t_vector_2d v1, t_vector_2d v2);
t_vector_3d	get_cross_poduct(t_vector_3d v1, t_vector_3d v2);
#endif
