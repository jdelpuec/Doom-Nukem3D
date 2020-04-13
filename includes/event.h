/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:33:08 by siwarin           #+#    #+#             */
/*   Updated: 2020/04/13 17:11:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

typedef struct		s_keyboard
{
	const Uint8		*state;
}					t_keyboard;

int					is_key_pressed(t_keyboard *k);
void				init_keyboard(t_keyboard *k);
int					handle_keyboard_misc(t_win *w, t_keyboard *k, t_ray *r);
void				handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k);
int					handle_keyboard_event(t_win *w, t_keyboard *k, t_ray *r);
void				handle_mouse_event(t_win *w, t_ray *r);
void				handle_mouse_mvt(t_win *w, t_ray *r);
void				mouse_button_down(t_win *w, t_ray *r);
void				free_quit(t_win *w, t_ray *r);

float				get_dir_angle(t_ray *r);
float				get_dot_poduct(t_vector_3d v1, t_vector_3d v2);
float				get_vector_length(t_vector_3d v);
t_vector_3d			normalize_vec(t_vector_3d v);
t_vector_3d			get_normal_wall(t_vector_2d v1, t_vector_2d v2);
t_vector_3d			get_cross_poduct(t_vector_3d v1, t_vector_3d v2);

#endif
