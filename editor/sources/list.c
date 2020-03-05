/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:07:11 by lubernar          #+#    #+#             */
/*   Updated: 2020/03/05 13:14:20 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"
#include "../includes/list.h"

void	init(t_lst *l, t_elem *e)
{
	l->first = NULL;
	l->last = NULL;
	l->lst_w = NULL;
	e->nb_maillon = 0;
}

void	push_back(t_lst *l, t_editor *edit)
{
	t_elem	*nouv;

	nouv = malloc(sizeof(t_elem));
	if (!nouv)
		exit(0);
	nouv->x1 = edit->x1_replace;
	nouv->y1 = edit->y1_replace;
	nouv->x2 = edit->x2_replace;
	nouv->y2 = edit->y2_replace;
	nouv->num_text = edit->texture_choosen - 1;
	nouv->nb_maillon = ++edit->nb_maillon;
	edit->count_walls++;
	nouv->prev = l->last;
	nouv->next = NULL;
	if (l->last)
		l->last->next = nouv;
	else
		l->first = nouv;
	l->last = nouv;
}

void	push_back_withoux1(t_lst *l, t_editor *edit, t_line *line)
{
	t_elem	*nouv;

	nouv = malloc(sizeof(t_elem));
	if (!nouv)
		exit(0);
	nouv->x1 = line->x1;
	nouv->y1 = line->y1;
	nouv->x2 = edit->x2_replace;
	nouv->y2 = edit->y2_replace;
	nouv->num_text = edit->texture_choosen - 1;
	nouv->nb_maillon = ++edit->nb_maillon;
	edit->count_walls++;
	nouv->prev = l->last;
	nouv->next = NULL;
	if (l->last)
		l->last->next = nouv;
	else
		l->first = nouv;
	l->last = nouv;
}

void	clear(t_lst *l)
{
	t_elem		*tmp;
	t_elem		*pelem;
	t_lst_wall	*tmp_w;

	pelem = l->first;
	while (pelem)
	{
		tmp = pelem;
		pelem = pelem->next;
		free(tmp);
	}
	if (l->lst_w != NULL)
	{
		while (l->lst_w)
		{
			tmp_w = l->lst_w;
			l->lst_w = l->lst_w->next;
			free(tmp_w);
		}
	}
	l->first = NULL;
	l->last = NULL;
}
