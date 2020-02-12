/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:33:08 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/10 10:41:43 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

typedef struct		s_keyboard
{
	const Uint8				*state;
}					t_keyboard;

int		is_key_pressed(t_keyboard *k);
void	init_keyboard(t_keyboard *k);
int		handle_keyboard_misc(t_win *w, t_keyboard *k);
void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k);
int		handle_keyboard_event(t_win *w, t_keyboard *k);
void	handle_mouse_event(t_win *w, t_ray *r);
void	handle_mouse_mvt(t_win *w, t_ray *r);
#endif
