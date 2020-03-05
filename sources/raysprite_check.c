/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raysprite_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:36:15 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/03/05 13:11:28 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"

void	display_spr_2(t_ray *r, t_win *w, t_text_tab sprt, t_wall_tex *st)
{
	int x;

	x = r->x - ((int)r->line_h >> 2);
	while (x++ < r->x + ((int)r->line_h))
	{
		r->y = (int)r->offset_start;
		st->tex_yf = 0;
		if ((int)st->tex_xf > r->inv.sprite[r->i].s.tex_w)
			break ;
		while (r->y++ < (int)r->offset_end)
		{
			if ((r->y >= 0 && r->y < WIN_H) && (x >= 0 && x < WIN_W))
			{
				st->tex_y = (int)st->tex_yf;
				st->tex_id = (int)(st->tex_y * r->inv.sprite[r->i].s.tex_w
															+ (int)st->tex_xf);
				if (st->tex_id < 900 && sprt.data[st->tex_id] != 0x00ff00)
					*((int *)w->surface->pixels
								+ (r->y * WIN_W + x)) = sprt.data[st->tex_id];
			}
			st->tex_yf += st->tex_scale;
		}
		st->tex_xf += st->tex_scale;
	}
}

int		check_frontground(t_ray *r)
{
	int			i;
	t_vector_2d	tmp;

	if (r->sector_count > 1)
		return (1);
	i = 0;
	while (i < r->sectors[r->player.sector].wall_count)
	{
		if ((check_seg_inter(r, r->sectors[r->player.sector].walls[i],
									&tmp.x, &tmp.y) == 1))
		{
			if (fabsf(tmp.x - r->player.position.x)
				< fabsf(r->hit_x - r->player.position.x)
				&& fabsf(tmp.y - r->player.position.y)
					< fabsf(r->hit_y - r->player.position.y))
				return (-1);
		}
		i++;
	}
	return (1);
}

int		check_spr_inter(t_ray *r, t_sprites sprite, float *h_x, float *h_y)
{
	int denom_is_pos;

	r->s10_x = sprite.pos.x + 0.5 - (sprite.pos.x - 0.5);
	r->s10_y = sprite.pos.y - 0.5 - (sprite.pos.y + 0.5);
	r->s32_x = r->ray_end.x - r->player.position.x;
	r->s32_y = r->ray_end.y - r->player.position.y;
	r->denom = r->s10_x * r->s32_y - r->s32_x * r->s10_y;
	if (r->denom == 0.0)
		return (0);
	denom_is_pos = r->denom > 0;
	r->s02_x = sprite.pos.x - r->player.position.x;
	r->s02_y = sprite.pos.y - r->player.position.y;
	r->s_denom = r->s10_x * r->s02_y - r->s02_x * r->s10_y;
	if ((r->s_denom < 0) == denom_is_pos)
		return (0);
	r->t_denom = r->s32_x * r->s02_y - r->s32_y * r->s02_x;
	if ((r->t_denom < 0) == denom_is_pos)
		return (0);
	if (((r->s_denom > r->denom) == denom_is_pos)
		|| ((r->t_denom > r->denom) == denom_is_pos))
		return (0);
	r->t = r->t_denom / r->denom;
	*h_x = sprite.pos.x + (r->t * r->s10_x);
	*h_y = sprite.pos.y + (r->t * r->s10_y);
	return (1);
}

int		sprite_close(t_vector_3d player, t_vector_3d sprite)
{
	float dist;

	dist = sqrtf((player.y - sprite.y) * (player.y - sprite.y)
				+ (player.x - sprite.x) * (player.x - sprite.x));
	if (dist < 3.0)
		return (-1);
	return (1);
}

int		detecte_sprite(t_win *w, t_ray *r)
{
	int ret;

	ret = -1;
	r->i = 0;
	while (r->i < r->inv.nb_sprites)
	{
		ret = draw_sprite(w, r);
		if (ret == 1)
			return (ret);
		r->i++;
	}
	return (0);
}
