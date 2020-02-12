/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:05:29 by cduverge          #+#    #+#             */
/*   Updated: 2019/12/17 17:42:16 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
#define DOOM_H

#include "SDL2/SDL.h"
#include "../libft/libft.h"

#define USAGE "Usage : ./doom-nukem <map> or ./doom-nukem editor <map>"

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Surface		*surface;
	int				nb_thread;
}					t_win;

typedef struct		s_texture
{
	int		width;
	int		height;
	void	*color;
}					t_texture;

typedef struct		s_vector_3d
{
	float	x;
	float	y;
	float	z;
}					t_vector_3d;

typedef struct		s_player
{
	t_vector_3d	position;
	t_vector_3d	velocity;
	float		angle;
	float		yaw;
	int			sector;
}					t_player;

typedef struct		s_wall
{
	int			portal_sector;
	int			id_wall;
	float		x1;
	float		y1;
	float		x2;
	float		y2;

	t_texture	texture;
}					t_wall;

typedef struct		s_sector
{
	int			wall_count;
	int			floor_height;
	int			ceil_height;
	int			brightness;
	int			id_floor;
	int			id_ceil;

	t_wall		*walls;
	t_texture	floor_tex;
	t_texture	ceil_tex;
}					t_sector;

typedef struct		s_env
{
	int			room;

	t_sector	*sct;
}					t_env;

//parsing.c
int		parsing(char *str, t_env *doom);
int		all_room(int fd, t_env *doom, int n_room);
int		check_data_sector(int fd, t_env *doom, int index);
void	give_me_data_wall(char *str, t_env *doom, int index);
int		data_wall(int fd, t_env *doom, int i);

//parsing_2.c
int		check_data_wall(int fd, t_env *doom, int i, int j);
void	fill_up_sector(char *str, t_env *doom, int i, int j);
float	ft_end_atof(char *str, unsigned long i, float res);
int		body_of_check_line(char *str, int i);
int		check_validity_map(t_env *doom);

//check_map.c
int		check_room_by_room(t_env *doom, int j);

//usefull.c
int		back_to_line(int fd);
int		number_or_dot(char *str);
int		check_entire_line(char *str);
int		check_line(char *str);
float	ft_atof(char *str);

//main.c
int		main(int ac, char **av);
#endif