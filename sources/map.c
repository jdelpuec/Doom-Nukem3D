/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:54:21 by lubernar          #+#    #+#             */
/*   Updated: 2020/01/06 16:54:14 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector*	map()
{
	t_sector *t;
	t = malloc(sizeof(t_sector) * 14);
	t[0].walls = malloc(sizeof(t_wall) * 6);
	t[0].wall_count = 6;
	t[0].floor_height = 0;
	t[0].ceil_height = 58;
	t[0].brightness = 1.0;
	t[0].walls[0].p1.x = -10;
	t[0].walls[0].p1.y = -10;
	t[0].walls[0].p2.x = -2.5;
	t[0].walls[0].p2.y = -10;

	t[0].walls[1].p1.x = 2.5;
	t[0].walls[1].p1.y = -10;
	t[0].walls[1].p2.x = 10;
	t[0].walls[1].p2.y = -10;

	t[0].walls[2].p1.x = -10;
	t[0].walls[2].p1.y = 10;
	t[0].walls[2].p2.x = -2.5;
	t[0].walls[2].p2.y = 10;

	t[0].walls[3].p1.x = 2.5;
	t[0].walls[3].p1.y = 10;
	t[0].walls[3].p2.x = 10;
	t[0].walls[3].p2.y = 10;

	t[0].walls[4].p1.x = -10;
	t[0].walls[4].p1.y = -10;
	t[0].walls[4].p2.x = -10;
	t[0].walls[4].p2.y = 10;

	t[1].walls = malloc(sizeof(t_wall) * 2);
	t[1].wall_count = 2;
	t[1].floor_height = 0;
	t[1].ceil_height = 58;
	t[1].brightness = 1.0;

	t[1].walls[0].p1.x = -2.5;
	t[1].walls[0].p1.y = -10;
	t[1].walls[0].p2.x = -2.5;
	t[1].walls[0].p2.y = -11;

	t[1].walls[1].p1.x = 2.5;
	t[1].walls[1].p1.y = -10;
	t[1].walls[1].p2.x = 2.5;
	t[1].walls[1].p2.y = -11;

	t[2].walls = malloc(sizeof(t_wall) * 2);
	t[2].wall_count = 2;
	t[2].floor_height = 5;
	t[2].ceil_height = 63;
	t[2].brightness = 1.0;

	t[2].walls[0].p1.x = -2.5;
	t[2].walls[0].p1.y = -11;
	t[2].walls[0].p2.x = -2.5;
	t[2].walls[0].p2.y = -12;

	t[2].walls[1].p1.x = 2.5;
	t[2].walls[1].p1.y = -11;
	t[2].walls[1].p2.x = 2.5;
	t[2].walls[1].p2.y = -12;

	t[3].walls = malloc(sizeof(t_wall) * 2);
	t[3].wall_count = 2;
	t[3].floor_height = 10;
	t[3].ceil_height = 68;
	t[3].brightness = 1.0;

	t[3].walls[0].p1.x = -2.5;
	t[3].walls[0].p1.y = -12;
	t[3].walls[0].p2.x = -2.5;
	t[3].walls[0].p2.y = -13;

	t[3].walls[1].p1.x = 2.5;
	t[3].walls[1].p1.y = -12;
	t[3].walls[1].p2.x = 2.5;
	t[3].walls[1].p2.y = -13;

	t[4].walls = malloc(sizeof(t_wall) * 2);
	t[4].wall_count = 2;
	t[4].floor_height = 10;
	t[4].ceil_height = 68;
	t[4].brightness = 1.0;

	t[4].walls[0].p1.x = -2.5;
	t[4].walls[0].p1.y = -12;
	t[4].walls[0].p2.x = -2.5;
	t[4].walls[0].p2.y = -13;

	t[4].walls[1].p1.x = 2.5;
	t[4].walls[1].p1.y = -12;
	t[4].walls[1].p2.x = 2.5;
	t[4].walls[1].p2.y = -13;

	t[5].walls = malloc(sizeof(t_wall) * 2);
	t[5].wall_count = 2;
	t[5].floor_height = 15;
	t[5].ceil_height = 73;
	t[5].brightness = 1.0;

	t[5].walls[0].p1.x = -2.5;
	t[5].walls[0].p1.y = -13;
	t[5].walls[0].p2.x = -2.5;
	t[5].walls[0].p2.y = -14;

	t[5].walls[1].p1.x = 2.5;
	t[5].walls[1].p1.y = -13;
	t[5].walls[1].p2.x = 2.5;
	t[5].walls[1].p2.y = -14;

	t[6].walls = malloc(sizeof(t_wall) * 2);
	t[6].wall_count = 2;
	t[6].floor_height = 20;
	t[6].ceil_height = 78;
	t[6].brightness = 1.0;

	t[6].walls[0].p1.x = -2.5;
	t[6].walls[0].p1.y = -14;
	t[6].walls[0].p2.x = -2.5;
	t[6].walls[0].p2.y = -15;

	t[6].walls[1].p1.x = 2.5;
	t[6].walls[1].p1.y = -14;
	t[6].walls[1].p2.x = 2.5;
	t[6].walls[1].p2.y = -15;

	t[7].walls = malloc(sizeof(t_wall) * 2);
	t[7].wall_count = 2;
	t[7].floor_height = 25;
	t[7].ceil_height = 83;
	t[7].brightness = 1.0;

	t[7].walls[0].p1.x = -2.5;
	t[7].walls[0].p1.y = -15;
	t[7].walls[0].p2.x = -2.5;
	t[7].walls[0].p2.y = -16;

	t[7].walls[1].p1.x = 2.5;
	t[7].walls[1].p1.y = -15;
	t[7].walls[1].p2.x = 2.5;
	t[7].walls[1].p2.y = -16;

	t[8].walls = malloc(sizeof(t_wall) * 2);
	t[8].wall_count = 2;
	t[8].floor_height = 30;
	t[8].ceil_height = 88;
	t[8].brightness = 1.0;

	t[8].walls[0].p1.x = -2.5;
	t[8].walls[0].p1.y = -16;
	t[8].walls[0].p2.x = -2.5;
	t[8].walls[0].p2.y = -17;

	t[8].walls[1].p1.x = 2.5;
	t[8].walls[1].p1.y = -16;
	t[8].walls[1].p2.x = 2.5;
	t[8].walls[1].p2.y = -17;

	t[9].walls = malloc(sizeof(t_wall) * 5);
	t[9].wall_count = 5;
	t[9].floor_height = 35;
	t[9].ceil_height = 113;
	t[9].brightness = 1.0;

	t[9].walls[0].p1.x = -2.5;
	t[9].walls[0].p1.y = -17;
	t[9].walls[0].p2.x = -20;
	t[9].walls[0].p2.y = -17;

	t[9].walls[1].p1.x = -20;
	t[9].walls[1].p1.y = -17;
	t[9].walls[1].p2.x = -20;
	t[9].walls[1].p2.y = -37;

	t[9].walls[2].p1.x = -20;
	t[9].walls[2].p1.y = -37;
	t[9].walls[2].p2.x = 20;
	t[9].walls[2].p2.y = -37;

	t[9].walls[3].p1.x = 20;
	t[9].walls[3].p1.y = -37;
	t[9].walls[3].p2.x = 20;
	t[9].walls[3].p2.y = -17;

	t[9].walls[4].p1.x = 20;
	t[9].walls[4].p1.y = -17;
	t[9].walls[4].p2.x = 2.5;
	t[9].walls[4].p2.y = -17;

	t[10].walls = malloc(sizeof(t_wall) * 4);
	t[10].wall_count = 4;
	t[10].floor_height = 40;
	t[10].ceil_height = 113;
	t[10].brightness = 1.0;

	t[10].walls[0].p1.x = -16;
	t[10].walls[0].p1.y = -25;
	t[10].walls[0].p2.x = -12;
	t[10].walls[0].p2.y = -25;

	t[10].walls[1].p1.x = -12;
	t[10].walls[1].p1.y = -25;
	t[10].walls[1].p2.x = -12;
	t[10].walls[1].p2.y = -27;

	t[10].walls[2].p1.x = -12;
	t[10].walls[2].p1.y = -28;
	t[10].walls[2].p2.x = -16;
	t[10].walls[2].p2.y = -25;

	t[10].walls[3].p1.x = -16;
	t[10].walls[3].p1.y = -28;
	t[10].walls[3].p2.x = -16;
	t[10].walls[3].p2.y = -25;

	t[11].walls = malloc(sizeof(t_wall) * 4);
	t[11].wall_count = 4;
	t[11].floor_height = 40;
	t[11].ceil_height = 113;
	t[11].brightness = 1.0;

	t[11].walls[0].p1.x = 16;
	t[11].walls[0].p1.y = -25;
	t[11].walls[0].p2.x = 12;
	t[11].walls[0].p2.y = -25;

	t[11].walls[1].p1.x = 12;
	t[11].walls[1].p1.y = -25;
	t[11].walls[1].p2.x = 12;
	t[11].walls[1].p2.y = -28;

	t[11].walls[2].p1.x = 12;
	t[11].walls[2].p1.y = -28;
	t[11].walls[2].p2.x = 16;
	t[11].walls[2].p2.y = -28;

	t[11].walls[3].p1.x = 16;
	t[11].walls[3].p1.y = -28;
	t[11].walls[3].p2.x = 16;
	t[11].walls[3].p2.y = -25;

	t[11].walls = malloc(sizeof(t_wall) * 2);
	t[11].wall_count = 2;
	t[11].floor_height = 0;
	t[11].ceil_height = 64;
	t[11].brightness = 1.0;

	t[11].walls[0].p1.x = 2.5;
	t[11].walls[0].p1.y = 10;
	t[11].walls[0].p2.x = 2.5;
	t[11].walls[0].p2.y = 20;

	t[11].walls[1].p1.x = -2.5;
	t[11].walls[1].p1.y = 10;
	t[11].walls[1].p2.x = -2.5;
	t[11].walls[1].p2.y = 20;

	t[12].walls = malloc(sizeof(t_wall) * 7);
	t[12].wall_count = 7;
	t[12].floor_height = 0;
	t[12].ceil_height = 128;
	t[12].brightness = 0.4;

	t[12].walls[0].p1.x = 2.5;
	t[12].walls[0].p1.y = 20;
	t[12].walls[0].p2.x = 15;
	t[12].walls[0].p2.y = 35;

	t[12].walls[1].p1.x = 15;
	t[12].walls[1].p1.y = 35;
	t[12].walls[1].p2.x = 15;
	t[12].walls[1].p2.y = 40;

	t[12].walls[2].p1.x = 15;
	t[12].walls[2].p1.y = 40;
	t[12].walls[2].p2.x = 2.5;
	t[12].walls[2].p2.y = 50;

	t[12].walls[3].p1.x = 2.5;
	t[12].walls[3].p1.y = 50;
	t[12].walls[3].p2.x = -2.5;
	t[12].walls[3].p2.y = 50;

	t[12].walls[4].p1.x = -2.5;
	t[12].walls[4].p1.y = 50;
	t[12].walls[4].p2.x = -15;
	t[12].walls[4].p2.y = 45;

	t[12].walls[5].p1.x = -15;
	t[12].walls[5].p1.y = 45;
	t[12].walls[5].p2.x = -15.5;
	t[12].walls[5].p2.y = 40;

	t[12].walls[6].p1.x = -15;
	t[12].walls[6].p1.y = 40;
	t[12].walls[6].p2.x = -2.5;
	t[12].walls[6].p2.y = 20;

	t[12].walls = malloc(sizeof(t_wall) * 3);
	t[12].wall_count = 3;
	t[12].floor_height = 0;
	t[12].ceil_height = 25;
	t[12].brightness = 0.4;

	t[12].walls[0].p1.x = 0;
	t[12].walls[0].p1.y = 30;
	t[12].walls[0].p2.x = 2.5;
	t[12].walls[0].p2.y = 35;

	t[12].walls[1].p1.x = 2.5;
	t[12].walls[1].p1.y = 35;
	t[12].walls[1].p2.x = -2.5;
	t[12].walls[1].p2.y = 35;

	t[12].walls[2].p1.x = -2.5;
	t[12].walls[2].p1.y = 35;
	t[12].walls[2].p2.x = 0;
	t[12].walls[2].p2.y = 30;

	return (t);
}
