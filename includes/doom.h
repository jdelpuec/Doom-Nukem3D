/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:50:31 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/17 12:18:18 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include "define.h"
# include "textures.h"
# include "fmod/fmod.h"

typedef struct		s_sound
{
	FMOD_SYSTEM	*fmod;
	FMOD_SOUND	*shot;
	FMOD_SOUND	*music;
	FMOD_SOUND	*reload;
	FMOD_RESULT	result;
	FMOD_BOOL	state;
	FMOD_CHANNELGROUP	*canal;
}					t_sound;

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Surface		*surface;
	TTF_Font		*font;
	TTF_Font		*font2;
	SDL_Color		fc;
	SDL_Surface		*mes;


	t_text_tab		text_list;
	int				nb_thread;
	int				color;

	int				fps;
	int				pressed;
	float			old_time;
	float			time;
	float			old_t;
	float			old_t_f;
	int				reload;
	int				fired;
	// added stuff
	t_sound			s;
	t_text_tab 		hud;
	t_text_tab 		hud2;
	t_text_tab 		hud3;
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
	int			id_text;
}					t_wall;

typedef struct		s_sector
{
	int			id_floor;
	int			id_ceil;
	int			wall_count;
	int			floor_height;
	int			ceil_height;
	float		brightness;

	t_vector_2d	min;
	t_vector_2d	max;
	t_wall		*walls;
	t_texture	floor_tex;
	t_texture	ceil_tex;
}					t_sector;

typedef struct		s_sprites
{
	t_vector_3d	pos;
	int			sector;
	int			id;
	int			pickable;
}					t_sprites;

typedef struct		s_env
{
	int			room;
	int			sprites;
	t_sector	*sct;
	t_player	player;
	t_sprites	*spt;
}					t_env;

//parsing.c
int		parser(int ac, char **av);
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
void	free_all_map(t_env *doom);
int		begin_player(int fd, t_env *doom);
int		free_and_return(char *str);
int		check_player(char *line);
//usefull.c
int		back_to_line(int fd);
int		number_or_dot(char *str);
int		check_entire_line(char *str);
int		check_line(char *str);
float	ft_atof(char *str);
//pars_sprites.c
int		check_sprites(int fd, t_env *doom, int nb);
int		get_nb_sprites(int fd, t_env *doom);
void	fill_up_sprite(char *str, t_env *doom, int i);
int		check_line_sprite(char *str);
//main.c
int		check_bright(int i, char *str, int spc);
int		all_check(t_env *doom, int fd);
void	fill_up_player(char *line, t_env *doom);
int		check_portal_sector(int fd, t_wall *walls, int i);
t_sector*			map();
float				deg_to_rad(float angle);
int					*int_malloc(char *name, int size);
char				*sting_malloc(char *name, int size);
char				**tab_malloc(char *name, int size);
unsigned char		*unsigned_char_malloc(char *name, int size);
void				display_l(int x, int y, t_win *sdl, t_text_tab tmp);
void			display(int x, int y, t_text_tab hud, t_win *win);


//hud.c
t_text_tab	find(char *str);
void 		init_ttf(t_win *sdl);
void		apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest);
void    print_messages(t_win *sdl);
#endif
