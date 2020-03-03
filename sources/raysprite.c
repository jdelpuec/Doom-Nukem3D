/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raysprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:40:33 by siwarin           #+#    #+#             */
/*   Updated: 2020/03/03 18:49:05 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"
#include "ft_math.h"
#include "event.h"

int		check_frontground(t_ray *r)
{
	int			i;
	t_vector_2d	tmp;

	if (r->sector_count > 1)
		return (1);
	i = 0;
	while (i < r->sectors[r->player.sector].wall_count)
	{
		if ((check_seg_intersection(r, r->sectors[r->player.sector].walls[i],
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

int     check_spr_inter(t_ray *r, t_sprites sprite, float *h_x, float *h_y)
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
    *h_x = sprite.pos.x + (r->t * r->s10_x);;
    *h_y = sprite.pos.y + (r->t * r->s10_y);;
    return (1);
}

void        display_spr_2(t_ray *r, t_win *w, t_text_tab sprt, t_wall_tex *st)
{
	int x;

	x = r->x - ((int)r->line_h >> 2);
	while (x++ < r->x + ((int)r->line_h))
	{
	    r->y = (int)r->offset_start;
	    st->tex_yf = 0;
		if ((int)st->tex_xf > r->inv.sprite[r->i].s.tex_w)
			break;
	    while (r->y++ < (int)r->offset_end)
	    {
	        if ((r->y >= 0 && r->y < WIN_H) && (x >= 0 && x < WIN_W))
	        {
	            st->tex_y = (int)st->tex_yf;
	            st->tex_id = (int)(st->tex_y * r->inv.sprite[r->i].s.tex_w +
															(int)st->tex_xf);
	            if (st->tex_id < 900 && sprt.data[st->tex_id] != 0x00ff00)
	                *((int *)w->surface->pixels + (r->y * WIN_W
	                    + x)) = sprt.data[st->tex_id];
	        }
	        st->tex_yf += st->tex_scale;
	    }
	    st->tex_xf += st->tex_scale;
	}
}

void        display_spr(t_ray *r, t_win *w, t_text_tab sprt)
{
    t_wall_tex st;

	st.tex_scale = r->inv.sprite[r->i].s.tex_w / r->line_h;
    st.tex_xf = 0;
	display_spr_2(r, w, sprt, &st);
	r->inv.sprite[r->i].display = 0;
}
int draw_sprite_2(t_ray *r, int s, t_win *w)
{
	if (check_frontground(r) == -1)
		return (0);
    r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
                    - r->player.position.x)) + ((r->hit_y - r->player.position.y)
                    * (r->hit_y - r->player.position.y)));
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
int     draw_sprite(t_win *w, t_ray *r)
{
    if (r->inv.sprite[r->i].sector == r->player.sector &&
        check_spr_inter(r, r->inv.sprite[r->i], &r->hit_x, &r->hit_y) == 1
        && r->inv.sprite[r->i].display == 1)
        return (draw_sprite_2(r, r->inv.sprite[r->i].sector, w));
    return (0);
}

int     detecte_sprite(t_win *w, t_ray *r)
{
    int         ret;

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
void    draw_sprite_view(t_win *w, t_ray *r)
{
    int         iter;
    int         running;

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
void  raysprite(t_win *w, t_ray *r)
{
    static int 	j;
	int 		i;

    if (j == 0)
    {
		i = 0;
        while (i < r->inv.nb_sprites)
        {
            if (r->inv.sprite[i].id == 1)
                r->inv.sprite[i].s = find("ress/noodles.bmp");
            else if (r->inv.sprite[i].id == 2)
                r->inv.sprite[i].s = find("ress/baguettes.bmp");
            else if (r->inv.sprite[i].id == 3)
                r->inv.sprite[i].s = find("ress/button.bmp");
			r->inv.sprite[i].display = 1;
            i++;
		}
    }
    j = 1;
    r->i = -1;
	while (r->i++ < r->inv.nb_sprites)
		if (r->inv.sprite[r->i].pickable)
			r->inv.sprite[r->i].display = 1;
    draw_sprite_view(w, r);
}