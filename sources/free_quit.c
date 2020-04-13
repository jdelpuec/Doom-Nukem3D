/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:50:17 by user42            #+#    #+#             */
/*   Updated: 2020/04/13 17:56:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventory.h"
#include "raycasting.h"

void    free_quit( t_win *w, t_ray *r)
{
    t_text_tab *tmp;
    t_text_tab *tmp2;

    tmp = w->text_list.next;
    free(w->text_list.data);
    free(w->text_list.path);
    free(w->text_list.prev);   
	free(r->sectors);
    while(tmp->next != NULL)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->data);
        // free(tmp2->path);
        free(tmp2);
    }
    free(w->text_list.data);
    free(r->check_sprt);
}