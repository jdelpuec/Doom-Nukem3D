/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:07:11 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/03 13:55:24 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"
#include "../includes/list.h"

void	init_lst_w(t_lst **lst, t_editor *edit)
{
	if (!((*lst)->lst_w = malloc(sizeof(t_lst_wall))))
		exit(0);
	if (lst == NULL)
		exit(0);
	(*lst)->lst_w->nb_walls = edit->count_walls;
	(*lst)->lst_w->sector_num = edit->sector_num;
	(*lst)->lst_w->walls_h = edit->walls_h;
	edit->lst_init_w = 1;
	(*lst)->lst_w->next = NULL;
}

void	lst_addend_w(t_lst *alst, t_lst_wall *new)
{
	t_lst_wall *lst_wall;

	if (!(lst_wall = malloc(sizeof(t_lst_wall))))
		exit(0);
	lst_wall = alst->lst_w;
	while (lst_wall->next != NULL)
		lst_wall = lst_wall->next;
	lst_wall->next = new;
}

void	fill_list_w(t_lst **lst, t_editor *edit)
{
	t_lst_wall	*new;

	if (!((new) = malloc(sizeof(t_lst_wall))))
		exit(0);
	new->nb_walls = edit->count_walls;
	new->sector_num = edit->sector_num;
	new->walls_h = edit->walls_h;
	new->next = NULL;
	lst_addend_w(*lst, new);
}
