/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raysprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:40:33 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/21 15:34:00 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "doom.h"

#include <stdio.h>

int		long_calcul(t_sprites s, t_ray *r)
{
	float	dist;
	float dist_sprite;

	dist = sqrtf(((s.pos.x - r->player.position.x)
				* (s.pos.x - r->player.position.x))
			+ ((s.pos.y - r->player.position.y)
				* (s.pos.y - r->player.position.y)));
	dist *= cos(r->ray_angle - r->player.angle);
	dist_sprite = dist * PLAYER_H;
	return (dist_sprite);
}
void	tri_sprite(t_sprites *s, int nb, t_ray *r)
{
	t_sprites	tmp;
	int			i;
	float		dist;
	float		dist2;

	i = 0;
	if (nb == 1)
		return ;
	while (i < nb)
	{
		dist = long_calcul(s[i], r);
		dist2 = long_calcul(s[i + 1], r);
		if (dist < dist2)
		{
			tmp = s[i + 1];
			s[i + 1] = s[i];
			s[i] = tmp;
		}
		++i;
	}
	return (tri_sprite(s, --nb, r));
}

int		check_spr_intersection(t_ray *r, t_sprites sprite, float *h_x, float *h_y)
{
	int denom_is_pos;

	r->s10_x = sprite.pos.x + 0.5 - sprite.pos.x;
	r->s10_y = sprite.pos.y + 0.5 - sprite.pos.y;
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

int		draw_sprite(t_win *w, t_ray *r, t_sprites *s)
{
	int i;
	int ret;

	i = 0;
	while (i < 3)
	{
		if (s[i].sector == r->player.sector
			&& (ret = check_spr_intersection(r, s[i], &r->hit_x, &r->hit_y)) == 1)
		{
//			printf("%i\n", ret);												///
			display((int)r->hit_x, (int)r->hit_y, s[i].s, w);
			//affichage
		}
//		printf("%i\n", ret);												///
		i++;
	}
	return (0);
}

void	draw_sprite_view(t_win *w, t_ray *r, t_sprites *s)
{
	int			iter;
	int			running;

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
			running = draw_sprite(w, r, s);
		}
		r->ray_angle += deg_to_rad(60.0) / WIN_W;
		r->x++;
	}
}

void  raysprite(t_win *w, t_ray *r)
{
  t_sprites s[3];
	s[0].s = find("ress/baguettes.bmp");
  s[0].pos.x = 8;
  s[0].pos.y = 4;
  s[0].pos.z = 32;
	s[0].sector = 0;
	s[1].s = find("ress/noodle.bmp");
	s[1].pos.x = 4;
  s[1].pos.y = 2;
  s[1].pos.z = 32;
	s[1].sector = 0;
	s[2].s = find("ress/button.bmp");
	s[2].pos.x = -7;
  s[2].pos.y = -2;
  s[2].pos.z = 35;
	s[2].sector = 0;
//  tri_sprite(s, 3, r);
	draw_sprite_view(w, r, s);
}
