/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:50:17 by user42            #+#    #+#             */
/*   Updated: 2020/04/14 21:33:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void    free_quit_w(t_win *w)
{
    t_text_tab  *tmp;
    t_text_tab  *tmp2;

    tmp = w->text_list.next;
    free(w->text_list.data);
    while(tmp->next != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->data);
        free(tmp2);
    }
    free(tmp->data);
    free(tmp);
    free(w->hud.data);
    free(w->hud2.data);
    free(w->hud3.data);
    free(w->font2);
    free(w->surface);
}

void    free_quit_r_2(t_ray *r)
{
    t_text_tab  *tmp;
    t_text_tab  *tmp2;

    tmp = r->gun.next;
    free(r->gun.data);
    while(tmp->next != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->data);
        free(tmp2);
    }
    free(tmp->data);
    free(tmp);
}

void    free_quit_r(t_ray *r)
{
    int         x;
    t_text_tab  *tmp;
    t_text_tab  *tmp2;

    x = 0;
    while (x < r->sector_count)
    	free(r->sectors[x++].walls);
	free(r->sectors);
    x = 0;
    while (x < r->inv.nb_sprites)
        free(r->inv.sprite[x++].s.data);
    free(r->inv.sprite);
    tmp = r->inv.list.next;
    free(r->inv.list.data);
    while(tmp->next != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->data);
        free(tmp2);
    }
    free(tmp->data);
    free(tmp);
    free_quit_r_2(r);
}

void    free_quit(t_win *w, t_ray *r)
{
    free_quit_w(w);
    free_quit_r(r);
}