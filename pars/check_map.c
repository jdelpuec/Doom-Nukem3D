/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:57:37 by cduverge          #+#    #+#             */
/*   Updated: 2019/12/17 17:41:33 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom.h"

int		check_room_by_room(t_env *doom, int j)
{
	int		i;
	float	a;
	float	b;

	i = 0;
	a = doom->sct[j].walls[i].x1;
	b = doom->sct[j].walls[i].y1;
	while (i < doom->sct[j].wall_count)
	{
		if (((i + 1) < doom->sct[j].wall_count)
				&& ((doom->sct[j].walls[i].x2 == doom->sct[j].walls[i + 1].x1)
				&& (doom->sct[j].walls[i].y2 == doom->sct[j].walls[i + 1].y1)))
			++i;
		else if ((i >= 2) && ((a == doom->sct[j].walls[i].x2)
					&& (b == doom->sct[j].walls[i].y2)))
			++i;
		else
			return (-1);
	}
	if (i != doom->sct[j].wall_count)
		return (-1);
	return (0);
}