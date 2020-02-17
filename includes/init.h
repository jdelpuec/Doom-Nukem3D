/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:37:51 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/17 11:02:29 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

void		init_sdl(t_win *w);
void		init_t_ray(t_ray *r, t_env *env);
t_text_tab	init_text(); //add path in arg;
#endif