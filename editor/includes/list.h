/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:21:42 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/08 15:22:12 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef	struct			s_lst_wall
{
	int					nb_walls;
	int					walls_h;
	int					sector_num;
	struct s_lst_wall	*next;
	struct s_lst_wall	*prev;
}						t_lst_wall;

typedef struct 			s_sprite
{
	int					x;
	int					y;
	int					num_sprite;
	int					nb_maillon;
	int					pickable;
	struct s_sprite		*prev;
	struct s_sprite		*next;
}						t_sprite;

typedef	struct			s_lst_sprite
{
	struct s_sprite		*last;
	struct s_sprite		*first;
}						t_lst_sprite;

typedef struct 			s_elem
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
	int					num_text;
	int					nb_maillon;
	struct s_elem 		*prev;
	struct s_elem 		*next;
}						t_elem;


typedef	struct			s_lst
{
	t_lst_wall			*lst_w;
	t_lst_sprite		*lst_s;
	struct s_elem		*last;
	struct s_elem		*first;
}						t_lst;

void		init(t_lst *lst, t_elem *e);
void		view(t_lst *l);
t_lst		*reverse_list(t_lst *lst, t_elem **e);
int			reverse_list_ornot(t_lst **lst);
void		clear(t_lst *l);


#endif
