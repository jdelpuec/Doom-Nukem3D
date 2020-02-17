/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doom_Nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:10:33 by siwarin           #+#    #+#             */
/*   Updated: 2020/02/17 15:00:17 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define DOOM_NUKEM_H

# include "../Libft/libft.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include <math.h>
# include "list.h"
# include "textures.h"
# include "malloc.h"

# define W 1920
# define H 1080

typedef struct	s_keyboard
{
	const Uint8	*state;
}				t_keyboard;

typedef struct	s_fps
{
	double		step;
	double		current;
	double		delta;
	double		last;
	double		count;
}				t_fps;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*ren;
	SDL_Surface *mes;
	SDL_Event	e;
	TTF_Font	*font;
	TTF_Font	*font2;
	t_keyboard	k;
	t_fps		f;
	int			fd;
	int			cx;
	int			cy;
	int			xmouse;
	int			ymouse;
	SDL_Color	fc;
	int			color;
	int			running;
}				t_sdl;

typedef struct		s_editor
{
	int			fd;
	int			texture_choosen;
	int			sprite_choosen;
	int			noodles;
	int			baguettes;
	int			x1_replace;
	int			y1_replace;
	int			x2_replace;
	int			y2_replace;
	int			first_x;
	int			first_y;
	int			lst_init;
	int			lst_init_w;
	int			saved;
	int			nb_clic;
	int			sector_num;
	int			count_walls;
	int			pressed;
	int			player_selected;
	float		play_x;
	float		play_y;
	float		sprite_x;
	float		sprite_y;
	int			player_onmap;
	int			walls_h;
	int			nb_maillon;
	int			nb_sprites;
	t_text_tab	list;
	t_text_tab	list_sprite;
	t_text_tab	list_player;
	t_text_tab	list_gravity;
}					t_editor;

typedef struct		s_line
{
	int					x;
	int					y;
	int					dx;
	int					dy;
	int					x1;
	int					y1;
	int					xinc;
	int					yinc;
	int					x2;
	int					y2;
}					t_line;

int			hook_keydown(t_sdl *sdl, t_lst *lst);
void		editdraw(t_sdl *sdl, t_editor *edit, t_line *line, t_lst **lst);
void		pixel(t_sdl *sdl, int x, int y);
void		apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *des);
void		draw_redsquare(t_sdl *sdl, int x, int y);
void		drawsquare(t_sdl *sdl, int x, int y);
void		drawmenu(t_sdl *sdl);
void		init_lst(t_lst **lst, t_editor *edit);
void		init_lst_w(t_lst **lst, t_editor *edit);
void		lst_addend(t_lst *alst, t_lst *new);
void		fill_list(t_lst **lst, t_editor *edit);
void		fill_list_without_x1(t_lst **lst, t_editor *edit, t_line *line);
void		fill_list_w(t_lst **lst, t_editor *edit);
void		write_in_file(t_sdl *sdl, t_editor *edit, t_lst **lst);
void		draw_line(t_line *line, t_sdl *sdl);
void		clic(t_sdl *sdl, t_line *line, t_editor *edit, t_lst **lst);
t_lst		*init_lst_ordered(t_lst *lst, t_lst *tmp);
t_lst		*fill_list_order(t_lst *lst, t_lst *tmp);
void		push_back(t_lst *l, t_editor *edit);
void		push_back_withoux1(t_lst *l, t_editor *edit, t_line *line);
void		init_edit(t_editor *edit);
void		draw_menu(t_sdl *sdl);
void		draw_line_on_click(t_line *line, t_sdl *sdl, t_editor *edit);
void		write_text(t_sdl *sdl, t_editor *edit);
void		textures_display(t_sdl *sdl, t_editor *edit);
void		find_coordinates(t_sdl *sdl, t_editor *edit);
void		find_coordinates2(t_sdl *sdl, t_editor *edit);
void		find_walls_coord(t_sdl *sdl, t_editor *edit, t_line *line, t_lst **lst);
void		draw_walls_lst(t_elem *begin, t_lst **lst, t_sdl *sdl);
void		player_sprites_coord(t_editor *edit, t_sdl *sdl);
t_elem		init_elem(void);
void		init_edit(t_editor *edit);
void		ft_init(t_sdl *sdl);
void		textures_area(t_sdl *sdl, t_editor *edit);
void		init_sprite(t_lst_sprite *l);
t_sprite	init_sprites(void);
void		push_back_sprite(t_lst *l, t_editor *edit);
void		find_sprites_coord(t_lst **l, t_editor *edit, t_sdl *sdl);
void		display(int x, int y, t_sdl *sdl, t_text_tab tmp);
void		display_l(int x, int y, t_sdl *sdl, t_text_tab tmp);
t_text_tab	display_next(t_sdl *sdl, t_sprite *s, t_text_tab tmp, t_editor *e);

/*
** colors
*/

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define ORANGE 0xFFA500
# define LIME 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define SILVER 0xC0C0C0
# define GRAY 0x808080
# define MAROON 0x800000
# define OLIVE 0x808000
# define GREEN 0x008000
# define PURPLE 0x800080
# define TEAL 0x008080
# define NAVY 0x000080

/*
** More awesome colors!
*/

# define CRIMSON 0xDC143C
# define CORAL 0xFF7F50
# define INDIAN_RED 0xCD5C5C
# define SALMON 0xFA8072
# define ORANGE_RED 0xFF4500

# define GOLD 0xFFD700
# define GOLDEN_ROD 0xDAA520
# define DARK_GOLDEN_ROD 0xB8860B
# define SADDLEBROWN 0x8B4513

# define LAWN_GREEN 0x7CFC00
# define DARK_GREEN 0x006400
# define FOREST_GREEN 0x228B22
# define PALE_GREEN 0x98FB98
# define SPRING_GREEN 0x00FF7F
# define SEA_GREEN 0x2E8B57
# define LIGHT_SEA_GREEN 0x20B2AA

# define DARK_SLATE_GRAY 0x2F4F4F
# define POWDER_BLUE 0xB0E0E6

# define AQUA_MARINE 0x7FFFD4
# define STEEL_BLUE 0x4682B4
# define SKY_BLUE 0x87CEEB
# define MIDNIGHT_BLUE 0x191970

# define INDIGO 0x4B0082
# define DARK_MAGENTA 0x8B008B
# define DEEP_PINK 0xFF1493
# define HOT_PINK 0xFF69B4
# define ORCHID 0xFF83FA

# define BEIGE 0xF5F5DC
# define ANTIQUE_WHITE 0xFAEBD7
# define WHEAT 0xF5DEB3
# define CORN_SILK 0xFFF8DC

# define LAVENDER 0xE6E6FA
# define FLORAL_WHITE 0xFFFAF0
# define ALICE_BLUE 0xF0F8FF
# define GHOST_WHITE 0xF8F8FF
# define HONEYDEW 0xF0FFF0
# define IVORY 0xFFFFF0
# define AZURE 0xF0FFFF
# define SNOW 0xFFFAFA
# define MISTY_ROSE 0xFFE4E1

# define DARK_GRAY 0x696969
# define GAINSBORO 0xDCDCDC
# define WHITE_SMOKE 0xF5F5F5

