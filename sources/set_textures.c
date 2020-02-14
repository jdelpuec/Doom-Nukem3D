/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 12:53:25 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/14 18:31:12 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
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
	// wt.intersec = sqrtf(wt.tx + wt.ty) * (w->text_list.tex_w / (65.0 * (1.0
	// 		/ (w->text_list.tex_w / r->player.position.z))));
	wt.tex_count = floorf(wt.intersec / w->text_list.tex_w);
	wt.full_len = wt.tex_count * w->text_list.tex_w;
	wt.tex_xf = wt.intersec - wt.full_len;
	wt.tex_scale = w->text_list.tex_w / r->line_h;
	wt.tex_yf = 0;
	return (wt);
}

t_floor_tex	set_floor_tex(t_text_tab *tmp, t_ray *r, t_sector sector, t_wall wall, int i)
{
	t_floor_tex	wf;
	(void)wall;

	wf.hit.x = (r->player.position.x - r->hit_x) / (WIN_W - r->x);
	wf.hit.y = (r->player.position.y - r->hit_y) / (WIN_H - r->offset_end);
	
	wf.tx = r->hit_x + wf.hit.x * i;
	wf.tx *= wf.tx;
	wf.ty = r->hit_y + wf.hit.y * i;
	wf.ty *= wf.ty;
	wf.intersec = sqrtf(wf.tx + wf.ty) * (tmp->tex_w / (16 * (1
			/ (tmp->tex_w / ((float)sector.ceil_height
			- (float)sector.floor_height)))));
	// wf.intersec = sqrtf(wf.tx + wf.ty) * (tmp->tex_w / (65.0 * (1.0
			// / (tmp->tex_w / r->player.position.z))));
	wf.tex_count = floorf(wf.intersec / tmp->tex_w);
	wf.full_len = wf.tex_count * tmp->tex_w;
	
	wf.tex_xf = 0;
	wf.tex_yf = wf.intersec - wf.full_len;
	wf.tex_scale = tmp->tex_w / (WIN_W - r->x);

	return (wf);
}


void		wall_textures(t_win *w, t_ray *r, t_sector sector, t_wall wall)
{
	int			i;
	t_wall_tex	wt;
	t_floor_tex	wf;
	t_text_tab	*tmp;

	tmp = &w->text_list;
	wt = set_wall_tex(w, r, sector, wall);
	// if (r->x % 35 == 0)
	// 	printf("x  = %d  ; fulllen  = %f   ; inter = %f \n",
	// 	r->x, wt.full_len, wt.intersec);

	i = -1;
	while (++i < (int)r->offset_start)
		if ((i >= 0 && i < WIN_H) 
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = GREY * r->light;
	i = (int)r->offset_start;
	while (i++ < (int)r->offset_end)
	{
		if ((i >= 0 && i < WIN_H) 
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
		{
			wt.tex_y = (int)wt.tex_yf;
			wt.tex_id = (int)(wt.tex_y * tmp->tex_w + (int)wt.tex_xf);
			if (wt.tex_id < tmp->tex_w * tmp->tex_w)
				*((int *)w->surface->pixels + (i * WIN_W + r->x)) = tmp->data[wt.tex_id];
		}
		wt.tex_yf += wt.tex_scale;
	}
	// tmp = tmp->next;
	wf = set_floor_tex(tmp, r, sector, wall, i);
	while (i++ < WIN_H)
	{
		if ((i >= 0 && i < WIN_H) 
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
		{
			wf.tex_x = (int)wf.tex_xf;
			wf.tex_id = (int)(wf.tex_y * tmp->tex_w + (int)wf.tex_xf);
			// if (wf.tex_id < tmp->tex_w * tmp->tex_w)
			if (wf.tex_y < tmp->tex_w && wf.tex_xf < tmp->tex_w)
				*((int *)w->surface->pixels + (i * WIN_W + r->x)) = tmp->data[wf.tex_id];
		}
		wf.tex_xf += wf.tex_scale;
	}

	// while (i++ < (int)r->offset_end)
	// 	if ((i >= 0 && i < WIN_H) 
	// 		&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
	// 		*((int *)w->surface->pixels + (i * WIN_W + r->x)) = (r->cur_sector + 1) * 25000 * r->light;
	while (i++ < WIN_H)
		if ((i >= 0 && i < WIN_H) 
			&& (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
			*((int *)w->surface->pixels + (i * WIN_W + r->x)) = DARK * r->light;
}