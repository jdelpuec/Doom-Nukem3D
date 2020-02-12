/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:50:31 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/12 18:02:10 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include "define.h"
# include "textures.h"
# include <SDL2/SDL.h>
# include "textures.h"

typedef struct		s_win
{
	int			pressed;
	float		old_t;
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Surface		*surface;

	t_text_tab		text_list;
	int				nb_thread;

	int				fps;
	float			old_time;
	float			time;

	// added stuff
	t_text_tab hud;
	t_text_tab hud2;
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
t_sector*			map();
float				deg_to_rad(float angle);
int					*int_malloc(char *name, int size);
char				*sting_malloc(char *name, int size);
char				**tab_malloc(char *name, int size);
unsigned char		*unsigned_char_malloc(char *name, int size);
void				display_l(int x, int y, t_win *sdl, t_text_tab tmp);
void    			init_gun(t_win *w, t_text_tab *gun_anim);


//hud.c
t_text_tab	find(char *str);
void	hud(t_win *sdl);
t_text_tab	handle_textures2(char **text_name, int y);
#endif
