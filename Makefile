# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 15:16:10 by jdelpuec          #+#    #+#              #
#    Updated: 2020/02/21 16:42:23 by lubernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  doom-nukem
SRC =   main.c handle_keyboard_event.c handle_mouse_event.c deg_to_rad.c \
        collision.c math.c inventory.c handle_textures.c ft_malloc.c \
        gun.c init_struct.c set_draw.c wall_draw.c set_textures.c\
        hud.c parsing.c check_map.c parser.c parsing_2.c usefull.c \
        pars_sprites.c hud_tools.c math_2.c print_messages.c handle_k_mvt.c \
        draw_portal_ceil.c is_key_pressed.c raysprite.c

OBJ =   $(SRC:.c=.o)

SRCDIR =    ./sources/
INCDIR =    ./includes/
LIBDIR =    ./libft/
OBJDIR =    ./objs/

SRCS =  $(addprefix $(SRCDIR), $(SRC))
OBJS =  $(addprefix $(OBJDIR), $(OBJ))

FLAGS = -Wall -Werror -Wextra
LIBFLAG =   $(LIBDIR)libft.a -L libft -l SDL2-2.0.0 -l SDL2_ttf-2.0.0 -l fmodex

all :   lib prefix $(NAME)

$(NAME) :   $(OBJS)
		gcc -g -fsanitize=address $(FLAGS) $(LIBFLAG) -o $(NAME) $(OBJS)
$(OBJDIR)%.o: $(SRCDIR)%.c
		gcc $(FLAGS) -I $(LIBDIR)$(INCDIR) -I $(INCDIR) -c -o $@ $^

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean > /dev/null

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

lib :
		@Make -C $(LIBDIR)

prefix :
		@mkdir -p $(OBJDIR)
		
re :    fclean all
