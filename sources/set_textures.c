/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:53:25 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/11 18:31:43 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"
#include "draw.h"

t_wall_tex	set_wall_tex(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	t_wall_tex	wt;

	wt.tx = wall.p1.x - r->hit_x;
	wt.tx *= wt.tx;
	wt.ty = wall.p1.y - r->hit_y;
	wt.ty *= wt.ty;
	// wt.intersec = sqrtf(wt.tx + wt.ty) * (w->text_list.tex_w / (65 * (1
			// / (w->text_list.tex_w / (float)sector.ceil_height
			// - (float)sector.floor_height))));
	(void)sector;
	wt.intersec = sqrtf(wt.tx + wt.ty) * (w->text_list.tex_w / (65.0 * (1.0
			/ (w->text_list.tex_w / 16.0))));
	wt.tex_count = floorf(wt.intersec / w->text_list.tex_w);
	wt.full_len = wt.tex_count * w->text_list.tex_w;
	wt.tex_xf = wt.intersec - wt.full_len;
	wt.tex_scale = w->text_list.tex_w / r->line_h;
	wt.tex_yf = 0;
	return (wt);
}

void		wall_textures(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	int			i;
	t_wall_tex	wt;

	i = 0;
	while (i++ < (int)r->offset_start)
		if ((i >= 0 && i < WIN_H) && (i > r->y_min && i < r->y_max - 1)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = GREY * r->light;
	wt = set_wall_tex(w, r, sector, wall);
	while (i++ < (int)r->offset_end)
	{
		if ((i >= 0 && i < WIN_H) && (i > r->y_min && i < r->y_max - 1)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
		{
			wt.tex_y = (int)wt.tex_yf;
			wt.tex_id = (int)(wt.tex_y * w->text_list.tex_w + (int)wt.tex_xf);
			if (wt.tex_id < w->text_list.tex_w * w->text_list.tex_w)
				*((int *)w->surface->pixels + (i * WIN_W + r->x)) = w->text_list.data[wt.tex_id];
		}
		wt.tex_yf += wt.tex_scale;
	}
	// while (i++ < (int)r->offset_end)
	// 	if ((i >= 0 && i < WIN_H) && (i > r->y_min && i < r->y_max - 1)
	// 		&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
	// 		*((int *)w->surface->pixels + (i * WIN_W + r->x)) = (r->cur_sector + 1) * 25000 * r->light;
	while (i++ < WIN_H)
		if ((i >= 0 && i < WIN_H) && (i > r->y_min && i < r->y_max - 1)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = DARK * r->light;
}