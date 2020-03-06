# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 14:02:40 by cduverge          #+#    #+#              #
#    Updated: 2020/03/06 11:40:40 by jdelpuec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  doom-nukem

SRC =   main.c handle_keyboard_event.c handle_mouse_event.c deg_to_rad.c \
		collision.c math.c inventory.c handle_textures.c ft_malloc.c \
		gun.c init_struct.c set_draw.c wall_draw.c set_textures.c\
		hud.c parsing.c check_map.c parser.c parsing_2.c usefull.c \
		pars_sprites.c hud_tools.c math_2.c print_messages.c handle_k_mvt.c \
		draw_portal_ceil.c is_key_pressed.c raysprite.c raysprite_check.c

OBJ = $(SRC:.c=.o)

SRCDIR  = ./sources/

INCDIR  = ./includes/

LIB = libft

LIBDIR = ./libft/

OBJDIR = ./objs/

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

FLAGS = -Wall -Werror -Wextra

LIBFLAG =   $(LIBDIR)libft.a -L libft -l SDL2-2.0.0 -l SDL2_ttf-2.0.0 -l fmodex

ROUGE = \033[31m
VERT = \033[32m
JAUNE = \033[33m
BLEU = \033[34m
ROSE = \033[35m
CYAN = \033[36m
BLANC = \033[37m

OKJAUNE = $(CYAN) ====> $(JAUNE)[OK]$(BLANC)

all: doom lib_rule prefix $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@gcc -c $(FLAGS) -I $(INCDIR) -I libft/ $< -o $@ -I./

$(NAME): $(OBJS) $(INCDIR)
	@echo "$(ROUGE)Doom-Nukem is compiling$(BLANC)"
	@gcc $(FLAGS) $(LIBFLAG) -o $(NAME) $(OBJS) && echo "- $(VERT)Objects Creation$(OKJAUNE)"
	@echo "$(VERT)Doom-Nukem is ready !"

lib_rule:
	@$(MAKE) -C $(LIB)
	@echo "$(VERT)libft is ready !"

norme:
	norminette $(SRCDIR)*.c $(INCDIR)*.h

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean > /dev/null
	@echo "- $(VERT)Deleted objects$(OKJAUNE)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean
	@echo "- $(VERT)Deleted exe$(OKJAUNE)"

re: fclean all

prefix:
	@mkdir -p $(OBJDIR)

doom:
	@echo "$(ROUGE)===================================="
	@echo "|             $(JAUNE)DOOM-NUKEM$(ROUGE)           |"
	@echo "===================================="

.PHONY: clean norme fclean re prefix make all
