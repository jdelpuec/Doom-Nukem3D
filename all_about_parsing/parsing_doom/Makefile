# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siwarin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 13:09:27 by siwarin           #+#    #+#              #
#    Updated: 2020/02/14 09:40:29 by cduverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRC =  main.c \
	   parsing.c \
	   usefull.c \
	   parsing_2.c \
	   check_map.c \
	   pars_sprites.c \

OBJ = $(SRC:.c=.o)

SRCDIR  = ./sources/

INCDIR  = ./includes/

LIB = libft

LIBDIR  = ./libft/

OBJDIR  = ./objs/

SRCS    = $(addprefix $(SRCDIR), $(SRC))

OBJS    = $(addprefix $(OBJDIR), $(OBJ))

FLAGS = -Wall -Werror -Wextra

LIBFLAG = $(LIBDIR)libft.a -L libft -l SDL2-2.0.0

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
	@gcc -c $(FLAGS) -I libft/ $< -o $@ -I./

$(NAME): $(OBJS)
	@echo "$(ROUGE)Doom-Nukem is compiling ...$(BLANC)"
	@gcc $(FLAGS) $(LIBFLAG) -o $(NAME) $(OBJS) && echo "- $(VERT)Objects Creation$(OKJAUNE)"
	@echo "$(VERT)Doom-Nukem is ready !"

lib_rule:
	@$(MAKE) -C $(LIB)
	@echo "$(VERT)libft is ready !"

norme:
	norminette $(SRCDIR)*.c $(INCDIR)*.h

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean
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
