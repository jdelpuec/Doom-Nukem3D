/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:02:38 by siwarin           #+#    #+#             */
/*   Updated: 2020/03/06 11:58:13 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct	s_ray
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
	t_player	start_pos;
	t_wall		old_wall;
	t_sector	*sectors;
	t_vector_2d	ray_end;
	t_invent	inv;
	t_text_tab	gun;
	t_text_tab	reload_gun;

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
	float		dist_sprite;
	float		offset_start;
	float		offset_end;
	float		line_h;

	float		space;
	float		thresh;
	float		speed;
	float		tmp;
	float		dir_angle;
	int			direction;
	int			gravity;

	int			x_1;
	int			y_1;
	int			x_2;
	int			y_2;

	int			*check_sprt;
}				t_ray;

typedef struct	s_wall_tex
{
	float		tx;
	float		ty;
	float		intersec;
	float		tex_count;
	float		full_len;
	float		tex_scale;
	float		tex_xf;
	float		tex_yf;
	int			tex_y;
	int			tex_id;
}				t_wall_tex;

typedef struct	s_floor_tex
{
	float		cor_dist;
	float		rl_dist;
	float		tx;
	float		ty;
	float		intersec;
	float		tex_count;
	float		full_len;
	float		tex_scale;
	float		tex_xf;
	float		tex_yf;
	int			tex_y;
	int			tex_x;
	int			tex_id;
	t_vector_2d	hit;
}				t_floor_tex;

float			check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p);
void			init_raycasting(t_ray *r);
void			wall_collision(t_ray *r, t_vector_3d wd, t_wall wall);
void			check_walls(t_ray *r);
float			get_dir_angle(t_ray *r);
float			get_dot_poduct(t_vector_3d v1, t_vector_3d v2);
float			get_vector_length(t_vector_3d v);
t_vector_3d		normalize_vec(t_vector_3d v);
t_vector_3d		get_normal_wall(t_vector_2d v1, t_vector_2d v2);
t_vector_3d		get_cross_poduct(t_vector_3d v1, t_vector_3d v2);
int				test_box(t_ray *r, t_vector_3d p, t_wall wall);
t_invent		*inventory(struct s_ray *r, t_win *sdl);
void			reload_gun(t_text_tab *reaload_anim, t_win *w);
t_text_tab		init_gun();
void			fire_gunshot(t_win *w, t_text_tab *gun_anim);
void			hud(t_win *sdl, t_ray *r);
float			deg_to_rad(float angle);
void			wall_textures(t_win *w, t_ray *r, t_sector sector, t_wall wall);
void			raysprite(t_win *w, t_ray *r);

#endif
