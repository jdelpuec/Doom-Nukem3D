/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:14:52 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/16 15:56:19 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"

t_lst	*reverse_list(t_lst *lst, t_elem **e)
{
	t_elem	*prev;
	t_elem	*current;
	t_elem	*next;
	int		tmp_x1;
	int		tmp_y1;

	e = &lst->first;
	prev = NULL;
	current = *e;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		tmp_x1 = current->x1;
		tmp_y1 = current->y1;
		current->x1 = current->x2;
		current->y1 = current->y2;
		current->x2 = tmp_x1;
		current->y2 = tmp_y1;
		current->next = prev;
		prev = current;
		current = next;
	}
	*e = prev;
	return (lst);
}

t_elem	*find_right_point(t_lst **lst, t_elem *tmp, int tmp_x1, int tmp_y1)
{
	while (tmp->next != NULL)
	{
		if (tmp_x1 < tmp->next->x1)
		{
			tmp_x1 = tmp->next->x1;
			tmp_y1 = tmp->next->y1;
		}
		if (tmp_x1 == tmp->next->x1 && tmp_y1 < tmp->next->y1)
			tmp_y1 = tmp->next->y1;
		tmp = tmp->next;
	}
	tmp = (*lst)->first;
	while (tmp->x1 != tmp_x1 && tmp->y1 != tmp_y1)
		tmp = tmp->next;
	return (tmp);
}

int		next_egal_null(t_elem *tmp)
{
	if (tmp->next == NULL)
	{
		if (tmp->prev->y1 < tmp->y1 && tmp->y2 < tmp->y1)
		{
			if (tmp->prev->x1 > tmp->x2)
				return (0);
			else
				return (1);
		}
		else if (tmp->prev->y1 > tmp->y2)
			return (1);
		else if (tmp->y2 > tmp->prev->y1)
			return (0);
	}
	return (-1);
}

int		reverse_list_ornot(t_lst **lst)
{
	int		tmp_x1;
	int		tmp_y1;
	t_elem	*tmp;

	tmp = (*lst)->first;
	tmp_x1 = tmp->x1;
	tmp_y1 = tmp->y1;
	tmp = find_right_point(lst, tmp, tmp_x1, tmp_y1);
	if (tmp->prev == NULL)
		return (1);
	if (next_egal_null(tmp) != -1)
		return (next_egal_null(tmp));
	if (tmp->prev->y1 < tmp->y1 && tmp->next->y1 < tmp->y1)
	{
		if (tmp->prev->x1 > tmp->next->x1)
			return (0);
		else
			return (1);
	}
	else if (tmp->prev->y1 > tmp->next->y1)
		return (1);
	else if (tmp->next->y1 > tmp->prev->y1)
		return (0);
	return (0);
}
