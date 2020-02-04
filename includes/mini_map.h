/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:21:25 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/04 14:24:09 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H

typedef struct		s_mini_map
{
    int     x;
    int     y;
    int     i;
    int     x_delta;
    int     y_delta;
    int     end_val;
    int     incr;

    double  decr;
    double  j;
}                   t_mini_map;


#endif