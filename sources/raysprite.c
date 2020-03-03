/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raysprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:40:33 by siwarin           #+#    #+#             */
/*   Updated: 2020/03/03 13:35:41 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"
#include "draw.h"
#include "ft_math.h"
#include "event.h"

int     long_calcul(t_sprites s, t_ray *r)
{
    float   dist;
    float dist_sprite;
    dist = sqrtf(((s.pos.x - r->player.position.x)
                * (s.pos.x - r->player.position.x))
            + ((s.pos.y - r->player.position.y)
                * (s.pos.y - r->player.position.y)));
    dist *= cos(r->ray_angle - r->player.angle);
    dist_sprite = dist * PLAY_H;
    return (dist_sprite);
}
void    tri_sprite(t_sprites *s, int nb, t_ray *r)
{
    t_sprites   tmp;
    int         i;
    float       dist;
    float       dist2;
    (void)s;
    i = 0;
    if (nb <= 1)
        return ;
    while (i < nb)
    {
        dist = long_calcul(r->inv.sprite[i], r);
        dist2 = long_calcul(r->inv.sprite[i + 1], r);
        if (dist < dist2)
        {
            tmp = r->inv.sprite[i + 1];
            r->inv.sprite[i + 1] = r->inv.sprite[i];
            r->inv.sprite[i] = tmp;
        }
        ++i;
    }
    return (tri_sprite(r->inv.sprite, --nb, r));
}
t_wall_tex  set_spt_tex(t_win *w, t_ray *r)
{
    t_wall_tex  wt;
(void)w;
    wt.tx = r->inv.sprite[r->i].pos.x + 0.05  - r->hit_x;
    wt.tx *= wt.tx;
    wt.ty = r->inv.sprite[r->i].pos.y - 0.05 - r->hit_y;
    wt.ty *= wt.ty;
    wt.intersec = sqrtf(wt.tx + wt.ty) * 20.0;
    wt.tex_count = floorf(wt.intersec / 30.0);
    wt.full_len = wt.tex_count * 30.0;
    wt.tex_xf = wt.intersec - wt.full_len;
    // wt.tex_xf = 0;
    wt.tex_scale = 30.0 / r->line_h;
    wt.tex_yf = 0;
    return (wt);
}
// int          display_text_spt(t_ray *r, t_win *w, t_text_tab *tmp, t_wall_tex *wt)
// {
//  int i;
//  i = (int)r->offset_start;
//  while (i++ < (int)r->offset_end)
//  {
//      if ((i >= 0 && i < WIN_H)
//          && (*((int *)w->surface->pixels + (i * WIN_W + r->x)) == 0))
//      {
//          wt->tex_y = (int)wt->tex_yf;
//          wt->tex_id = (int)(wt->tex_y * tmp->tex_w + (int)wt->tex_xf);
//          if (wt->tex_id < tmp->tex_w * tmp->tex_w)
//              *((int *)w->surface->pixels
//              + (i * WIN_W + r->x)) = tmp->data[wt->tex_id];
//      }
//      wt->tex_yf += wt->tex_scale;
//  }
//  return (i);
// }
// void     sprite_textures(t_win *w, t_ray *r)
// {
//  t_wall_tex  wt;
//  t_text_tab  *tmp;
//  tmp = &w->text_list;
//  wt = set_spt_tex(w, r);
//  display_text_spt(r, w, tmp, &wt);
// }
int     check_spr_inter(t_ray *r, t_sprites sprite, float *h_x, float *h_y)
{
    int denom_is_pos;
    r->s10_x = sprite.pos.x + 0.05 - (sprite.pos.x - 0.05);
    r->s10_y = sprite.pos.y - 0.05 - (sprite.pos.y + 0.05);
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
    // *h_x = (sprite.pos.x - 0.05) + (r->t * r->s10_x);
    // *h_y = (sprite.pos.y + 0.05) + (r->t * r->s10_y);
    *h_x = sprite.pos.x + (r->t * r->s10_x);;
    *h_y = sprite.pos.y + (r->t * r->s10_y);;
    return (1);
}
void        display_spr(t_ray *r, t_win *w, t_text_tab sprt)
{
    int i;
    int x;
    t_wall_tex st;
    x = r->x - ((int)r->line_h >> 2);
    st = set_spt_tex(w, r);
    st.tex_xf = 0;
    while (x++ < r->x + ((int)r->line_h >> 2))
    {
        i = (int)r->offset_start;
        st.tex_yf = 0;
        while (i++ < (int)r->offset_end)
        {
            if ((i >= 0 && i < WIN_H) && (x >= 0 && x < WIN_W))
            {
                st.tex_y = (int)st.tex_yf;
                st.tex_id = (int)(st.tex_y * 30 + (int)st.tex_xf);
                if (st.tex_id < 900 && sprt.data[st.tex_id] != 0x00ff00)
                    *((int *)w->surface->pixels + (i * WIN_W
                        + x)) = sprt.data[st.tex_id];
            }
            st.tex_yf += st.tex_scale;
        }
        st.tex_xf += st.tex_scale;
    }
    r->check_sprt[r->inv.sprite[r->i].id - 1] = -1;
}
int draw_sprite_2(t_ray *r, int s, t_win *w)
{
    r->dist = sqrtf(((r->hit_x - r->player.position.x) * (r->hit_x
                    - r->player.position.x)) + ((r->hit_y - r->player.position.y)
                    * (r->hit_y - r->player.position.y)));
    r->dist *= cos(r->ray_angle - r->player.angle);
    r->dist_sprite = r->dist * PLAY_H;
    r->offset_start = (WIN_H >> 1) + ((r->player.position.z
                - (r->sectors[s].floor_height + 30)) / r->dist_sprite) * r->dist_pp;
    r->offset_end = (WIN_H >> 1) + ((r->player.position.z
                - r->sectors[s].floor_height) / r->dist_sprite) * r->dist_pp;
    r->line_h = r->offset_end - r->offset_start;
//  sprite_textures(w, r);
    display_spr(r, w, r->inv.sprite[r->i].s);
    return (1);
}
int     draw_sprite(t_win *w, t_ray *r)
{
    if (r->inv.sprite[r->i].sector == r->player.sector &&
        check_spr_inter(r, r->inv.sprite[r->i], &r->hit_x, &r->hit_y) == 1
        && r->check_sprt[r->inv.sprite[r->i].id - 1] != -1
        && r->inv.sprite[r->i].pickable == 1)
        return (draw_sprite_2(r, r->inv.sprite[r->i].sector, w));
    return (0);
}
int     sprite_loop(t_win *w, t_ray *r)
{
    int ret;
    ret = draw_sprite(w, r);
    if (ret == 1)
        return (1);
    r->i++;
    return (2);
}
int     detecte_sprite(t_win *w, t_ray *r)
{
    int         ret;
    r->i = 0;
    while (r->i < r->inv.nb_sprites)
    {
        ret = sprite_loop(w, r);
        if (ret == 0 || ret == 1)
            return (ret);
    }
    return (0);
}
void    draw_sprite_view(t_win *w, t_ray *r)
{
    int         iter;
    int         running;
    r->x = 0;
    r->ray_angle = (deg_to_rad(-30.0) + r->player.angle);
    SDL_memset(r->check_sprt, 0, r->inv.nb_sprites);
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
    static int j;
    if (j == 0)
    {
        r->inv.sprite[0].s = find("ress/noodles.bmp");
        r->inv.sprite[0].s.w = 30;
        r->inv.sprite[0].s.h = 30;
        /*r->inv.sprite[1].s = find("ress/noodle.bmp");
        r->inv.sprite[1].s.w = 30;
        r->inv.sprite[1].s.h = 30;
        r->inv.sprite[2].s = find("ress/noodles.bmp");
        r->inv.sprite[2].s.w = 30;
        r->inv.sprite[2].s.h = 30;
        r->inv.sprite[3].s = find("ress/bullet.bmp");
        r->inv.sprite[3].s.w = 30;
        r->inv.sprite[3].s.h = 30;*/
    }
    j = 1;
    tri_sprite(r->inv.sprite, r->inv.nb_sprites -1, r);
    draw_sprite_view(w, r);
}