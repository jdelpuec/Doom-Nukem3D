/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:53:25 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/19 15:30:18 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"
#include "ft_math.h"

t_wall_tex	set_wall_tex(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	t_wall_tex	wt;

	wt.tx = wall.p2.x - r->hit_x;
	wt.tx *= wt.tx;
	wt.ty = wall.p2.y - r->hit_y;
	wt.ty *= wt.ty;
	wt.intersec = sqrtf(wt.tx + wt.ty) * (w->text_list.tex_w / (16 * (1
			/ (w->text_list.tex_w / ((float)sector.ceil_height
			- (float)sector.floor_height)))));
	wt.tex_count = floorf(wt.intersec / w->text_list.tex_w);
	wt.full_len = wt.tex_count * w->text_list.tex_w;
	wt.tex_xf = wt.intersec - wt.full_len;
	wt.tex_scale = w->text_list.tex_w / r->line_h;
	wt.tex_yf = 0;
	return (wt);
}

int			display_text(t_ray *r, t_win *w, t_text_tab *tmp, t_wall_tex *wt)
{
	int i;

	i = (int)r->offset_start;
	while (i++ < (int)r->offset_end)
	{
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
		{
			wt->tex_y = (int)wt->tex_yf;
			wt->tex_id = (int)(wt->tex_y * tmp->tex_w + (int)wt->tex_xf);
			if (wt->tex_id < tmp->tex_w * tmp->tex_w)
				*((int *)w->surface->pixels
				+ (i * WIN_W + r->x)) = tmp->data[wt->tex_id];
		}
		wt->tex_yf += wt->tex_scale;
	}
	return (i);
}

void		wall_textures(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	int			i;
	t_wall_tex	wt;
	t_text_tab	*tmp;

	tmp = &w->text_list;
	wt = set_wall_tex(w, r, sector, wall);
	i = -1;
	while (++i < (int)r->offset_start)
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = GREY * r->light;
	i = display_text(r, w, tmp, &wt);
	while (i++ < WIN_H)
		if ((i >= 0 && i < WIN_H)
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = DARK;
}
