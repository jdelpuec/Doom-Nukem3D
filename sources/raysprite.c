/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raysprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:40:33 by siwarin           #+#    #+#             */
/*   Updated: 2020/03/05 17:43:53 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"

void	display_spr(t_ray *r, t_win *w, t_text_tab sprt)
{
	t_wall_tex st;

	st.tex_scale = r->inv.sprite[r->i].s.tex_w / r->line_h;
	st.tex_xf = 0;
	display_spr_2(r, w, sprt, &st);
	r->inv.sprite[r->i].display = 0;
}

int		draw_sprite_2(t_ray *r, int s, t_win *w)
{
	if (sprite_close(r->player.position, r->inv.sprite[r->i].pos) == -1)
		return (1);
	if (check_frontground(r) == -1)
		return (0);
	r->dist = sqrtf((r->hit_x - r->player.position.x)
		* (r->hit_x - r->player.position.x) + (r->hit_y - r->player.position.y)
			* (r->hit_y - r->player.position.y));
	r->dist *= cos(r->ray_angle - r->player.angle);
	r->dist_sprite = r->dist * PLAY_H;
	r->offset_start = (WIN_H >> 1) + ((r->player.position.z
			- (r->sectors[s].floor_height + 15)) / r->dist_sprite) * r->dist_pp;
	r->offset_end = (WIN_H >> 1) + ((r->player.position.z
			- r->sectors[s].floor_height) / r->dist_sprite) * r->dist_pp;
	r->line_h = r->offset_end - r->offset_start;
	display_spr(r, w, r->inv.sprite[r->i].s);
	return (1);
}

int		draw_sprite(t_win *w, t_ray *r)
{
	if (r->inv.sprite[r->i].sector == r->player.sector &&
		check_spr_inter(r, r->inv.sprite[r->i], &r->hit_x, &r->hit_y)
									== 1 && r->inv.sprite[r->i].display == 1)
		return (draw_sprite_2(r, r->inv.sprite[r->i].sector, w));
	return (0);
}

void	draw_sprite_view(t_win *w, t_ray *r)
{
	int iter;
	int running;

	r->x = 0;
	r->ray_angle = (deg_to_rad(-30.0) + r->player.angle);
	while (r->x < WIN_W)
	{
		r->last_sec = -2;
		r->ray_end.x = r->player.position.x + cosf(r->ray_angle) * 200.0;
		r->ray_end.y = r->player.position.y - sinf(r->ray_angle) * 200.0;
		r->cur_sector = r->player.sector;
		r->y_min = 0;
		r->y_max = WIN_H - 1;
		iter = 0;
		running = 0;
		while (running == 0)
		{
			iter++;
			if (iter >= SECTOR_ITER_MAX)
				break ;
			running = detecte_sprite(w, r);
		}
		r->ray_angle += deg_to_rad(60.0) / WIN_W;
		r->x++;
	}
}

void	raysprite(t_win *w, t_ray *r)
{
	static int	j;
	int			i;

	if (j == 0)
	{
		i = 0;
		while (i < r->inv.nb_sprites)
		{
			if (r->inv.sprite[i].id == 1)
				r->inv.sprite[i].s = find("ressources/noodles.bmp");
			else if (r->inv.sprite[i].id == 2)
				r->inv.sprite[i].s = find("ressources/baguettes.bmp");
			else if (r->inv.sprite[i].id == 3)
				r->inv.sprite[i].s = find("ressources/firebolt.bmp");
			r->inv.sprite[i].display = 1;
			i++;
		}
	}
	j = 1;
	r->i = -1;
	while (r->i++ < r->inv.nb_sprites)
		if (r->inv.sprite[r->i].pickable || r->inv.sprite[r->i].id == 3)
			r->inv.sprite[r->i].display = 1;
	draw_sprite_view(w, r);
}
