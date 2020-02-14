/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:50:31 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/14 17:55:20 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include "../Libft/libft.h"
# include "get_next_line.h"
# include "define.h"
# include "../includes/SDL2/SDL.h"
# include "inventory.h"
# include "textures.h"

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Surface		*surface;
	int				nb_thread;

	int				fps;
	float			old_time;
	float			time;
}					t_win;

typedef struct		s_texture
{
	int		width;
	int		height;
	void	*color;
}					t_texture;

typedef struct		s_vector_2d
{
	float	x;
	float	y;
}					t_vector_2d;

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

	t_vector_2d	p1;
	t_vector_2d	p2;
	t_texture	texture;
}					t_wall;

typedef struct		s_sector
{
	int			wall_count;
	int			floor_height;
	int			ceil_height;
	float		brightness;

	t_wall		*walls;
	t_texture	floor_tex;
	t_texture	ceil_tex;
}					t_sector;

t_sector*			map();
float				deg_to_rad(float angle);
int					*int_malloc(char *name, int size);
char				*sting_malloc(char *name, int size);
char				**tab_malloc(char *name, int size);
unsigned char		*unsigned_char_malloc(char *name, int size);
#endif
