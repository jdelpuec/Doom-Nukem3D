/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:50:17 by user42            #+#    #+#             */
/*   Updated: 2020/04/13 18:47:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void    free_quit( t_win *w, t_ray *r)
{
    int         x;
    t_text_tab  *tmp;
    t_text_tab  *tmp2;

    x = 0;
    tmp = w->text_list.next;
    free(w->text_list.data);
    free(w->text_list.prev);
    while(tmp->next != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->data);
        free(tmp2);
    }
    free(tmp->data);
    free(tmp);
    while (x < r->sector_count)
    	free(r->sectors[x++].walls);
	free(r->sectors);
    free(r->check_sprt);
}