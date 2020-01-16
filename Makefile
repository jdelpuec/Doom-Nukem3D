# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 15:16:10 by jdelpuec          #+#    #+#              #
#    Updated: 2020/01/06 16:47:54 by jdelpuec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	DOOM-NUKEM

SRC	=	main.c handle_keyboard_event.c handle_mouse_event.c	map.c deg_to_rad.c\

OBJ =	$(SRC:.c=.o)

SRCDIR =	./sources/
INCDIR =	./includes/
LIBDIR =	./libft/
OBJDIR =	./objs/

SRCS =	$(addprefix $(SRCDIR), $(SRC))
OBJS =	$(addprefix $(OBJDIR), $(OBJ))

FLAGS =	-Wall -Werror -Wextra
LIBFLAG =	$(LIBDIR)libft.a -L libft -l SDL2-2.0.0

all :	lib prefix $(NAME)

$(NAME) :	$(OBJS)
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

re :	fclean all