/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:14:58 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/01/07 15:01:02 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

typedef struct		s_line
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
}                   t_line;


#endif