/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:50:31 by ebonafi           #+#    #+#             */
/*   Updated: 2020/02/21 11:29:34 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include "fmod/fmod.h"

/*
** WINDOW
*/

# define WIN_W 800
# define WIN_H 680
# define FPS 60.0

/*
** RAYCASTING
*/

# define SECTOR_ITER_MAX 16

# define PLAYER_H 32

# define DARK 0x303030
# define GREY 0x808080
# define BLUE 0x0000ff
# define GREEN 0x00ff00
# define RED 0xff0000

# define HEADER_SIZE 54

typedef struct      s_text_tab
{
	int					id;
	int					tex_w;
    int					w;
    int					h;
    char				*path;
    int					*data;
    struct s_text_tab   *next;
    struct s_text_tab   *prev;
}                   t_text_tab;

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
	int			gravity;
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
	t_text_tab	s;
}					t_sprites;

typedef struct		s_env
{
	int			room;
	int			sprites;
	t_sector	*sct;
	t_player	player;
	t_sprites	*spt;
}					t_env;

typedef struct		s_keyboard
{
	const Uint8				*state;
}					t_keyboard;

typedef struct		s_inventory
{
	char	**inventory;
	int		inventory_display[4];
}					t_inventory;

typedef struct		s_parsing_sprite
{
	int						x;
	int						y;
	int						z;
	int						num_sprite;
	int						nb_maillon;
	int						pickable;
	int						nb_noodles;
	struct s_parsing_sprite	*next;
	struct s_parsing_sprite	*prev;
}					t_parsing_sprite;

typedef struct		s_invent
{
	t_sprites			*sprite;
	t_text_tab			list;
	t_text_tab			tmp;
	t_inventory			invent;
	int					init;
	int					nb_bullet;
	int					nb_hp;
	int					anim;
	int					nb_noodles;
	int					nb_baguette;
	int					nb_noodles_c;
	int					nb_sprites;
}					t_invent;

typedef struct		s_wall_tex
{
	float	tx;
	float	ty;
	float	intersec;
	float	tex_count;
	float	full_len;
	float	tex_scale;
	float	tex_xf;
	float	tex_yf;
	int		tex_y;
	int		tex_id;
}					t_wall_tex;

typedef struct		s_floor_tex
{
	float	cor_dist;
	float	rl_dist;
	float	tx;
	float	ty;
	float	intersec;
	float	tex_count;
	float	full_len;
	float	tex_scale;
	float	tex_xf;
	float	tex_yf;
	int		tex_y;
	int		tex_x;
	int		tex_id;

	t_vector_2d	hit;
}					t_floor_tex;

typedef struct		s_ray
{
	int			x;
	int			y;
	int			i;
	int			sector_count;
	int			cur_sector;
	int			last_sec;
	float		dist_pp;
	float		ray_angle;

	t_player	player;
	t_wall		old_wall;
	t_sector	*sectors;
	t_vector_2d	ray_end;
	t_invent	inv;
	t_text_tab	gun;
	t_text_tab	reload_gun;

	float		s02_x;
	float		s02_y;
	float		s10_x;
	float		s10_y;
	float		s32_x;
	float		s32_y;
	float		s_denom;
	float		t_denom;
	float		denom;
	float		denom_is_pos;
	float		t;

	float		hit_x;
	float		hit_y;
	float		light;
	float		dist;
	float		dist_wall;
	float		offset_start;
	float		offset_end;
	float		line_h;
	int			y_min;
	int			y_max;
	int			last_y_min;
	int			last_y_max;

	float		space;
	float		thresh;
	float		speed;
	float		tmp;
	float		dir_angle;
	int			direction;
	int			gravity;


	int		x_1;
	int		y_1;
	int		x_2;
	int		y_2;
}					t_ray;

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
void	fill_up_sprite_coor(char *str, t_env *doom, int i);
int		check_if_sprites(int fd);
int		check_sprite_id(int fd, t_env *doom, int i);
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
//draw.h
void	drawing(t_win *w, t_ray *r, t_keyboard *k);
void	draw_player_view(t_win *w, t_ray *r);
int		draw_sector(t_win *w, t_ray *r);
int		sector_loop(t_win *w, t_ray *r, t_sector sector, t_wall wall);
int		draw_wall(t_win *w, t_ray *r, t_sector sector, t_wall wall);

int		check_seg_intersection(t_ray *r, t_wall wall, float *h_x, float *h_y);

float		check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p);

void		init_raycasting(t_ray *r);
//event.h
int		is_key_pressed(t_keyboard *k);
void	init_keyboard(t_keyboard *k);
int		handle_keyboard_misc(t_win *w, t_keyboard *k);
void	handle_keyboard_mvt(t_win *w, t_ray *r, t_keyboard *k);
int		handle_keyboard_event(t_win *w, t_keyboard *k);
void	handle_mouse_event(t_win *w, t_ray *r);
void	handle_mouse_mvt(t_win *w, t_ray *r);

void    wall_collision(t_ray *r, t_vector_3d wd, t_wall wall);
float		get_dir_angle(t_ray *r);
float		get_dot_poduct(t_vector_3d v1, t_vector_3d v2);
float		get_vector_length(t_vector_3d v);
t_vector_3d	normalize_vec(t_vector_3d v);
t_vector_3d	get_normal_wall(t_vector_2d v1, t_vector_2d v2);
t_vector_3d	get_cross_poduct(t_vector_3d v1, t_vector_3d v2);
//ft_math.c
float	minf(float a, float b);
float	maxf(float a, float b);
t_vector_2d	vec2_sub(t_vector_2d a, t_vector_2d b);
//init.h
void		init_sdl(t_win *w);
void		init_t_ray(t_ray *r, t_env *env);
t_text_tab	init_text(); //add path in arg;
//malloc.h
int					*int_malloc(char *name, int size);
char				*sting_malloc(char *name, int size);
char				**tab_malloc(char *name, int size);
unsigned char		*unsigned_char_malloc(char *name, int size);
//rayscating.h
float		check_line_point(t_vector_2d l1, t_vector_2d l2, t_vector_3d p);
void		init_raycasting(t_ray *r);
void		wall_collision(t_ray *r, t_vector_3d wd, t_wall wall);
float		get_dir_angle(t_ray *r);
float		get_dot_poduct(t_vector_3d v1, t_vector_3d v2);
float		get_vector_length(t_vector_3d v);
t_vector_3d	normalize_vec(t_vector_3d v);
t_vector_3d	get_normal_wall(t_vector_2d v1, t_vector_2d v2);
t_vector_3d	get_cross_poduct(t_vector_3d v1, t_vector_3d v2);

t_invent	*inventory(struct s_ray *r, t_win *sdl);
void 		reload_gun(t_text_tab *reaload_anim, t_win *w);
t_text_tab  init_gun();
void    	fire_gunshot(t_win *w, t_text_tab *gun_anim);
void		hud(t_win *sdl, t_ray *r);
float				deg_to_rad(float angle);
void		wall_textures(t_win *w, t_ray *r, t_sector sector, t_wall wall);
void		raysprite(t_win *w, t_ray *r);
//textures.h
t_text_tab      handle_textures(char **text_name, int y);
void		    fill_text_tab(int fd, unsigned char *buff_header, t_text_tab *new, int x);
unsigned char	*handle_header(int fd);
void            start_list(t_text_tab **list);
void            list_reach(t_text_tab **list, char *path);
#endif
