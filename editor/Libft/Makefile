# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/10 20:09:46 by cduverge          #+#    #+#              #
#    Updated: 2020/02/16 14:24:17 by lubernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c \
			get_next_line.c \
			ft_swap.c \
			ft_power.c \
			ft_sqrt.c \
			ft_factorial.c \
			ft_count_words.c \
			ft_strrev.c \
			ft_is_sort.c \
			ft_strcapitalize.c \
			ft_lstmap.c \
			ft_lstiter.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstnew.c \
			ft_itoa.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_strmap.c \
			ft_striteri.c \
			ft_striter.c \
			ft_putnbr_fd.c \
			ft_putnbr.c \
			ft_strsplit.c \
			ft_strjoin.c \
			ft_strsub.c \
			ft_strnequ.c \
			ft_strequ.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putstr.c \
			ft_putchar.c \
			ft_strclr.c \
			ft_strdel.c \
			ft_strnew.c \
			ft_memdel.c \
			ft_memalloc.c \
			ft_memmove.c \
			ft_memcmp.c \
			ft_memchr.c \
			ft_strlcat.c \
			ft_strrchr.c \
			ft_strchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_memcpy.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memccpy.c \
			ft_memset.c \
			ft_strcat.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnstr.c \
			ft_strstr.c \
			ft_print_tab.c \
			ft_strendcmp.c \
			ft_is_prime.c \
			ft_lstadd.c \
			ft_abs.c \
			ft_atof.c

OBJ = $(SRCS:.c=.o)

VERT = \033[32m
CYAN = \033[36m
JAUNE = \033[33m
ROUGE = \033[31m
BLANC = \033[37m

OKVERT = $(CYAN) ====> $(VERT)[OK]$(BLANC)
KOROUGE = $(CYAN) ====> $(ROUGE)[KO]$(BLANC)

all: $(NAME)

$(NAME):
	@echo "$(ROUGE)Libft is compiling$(BLANC)"
	@$(CC) $(FLAGS) -c $(SRCS) && echo "- $(JAUNE)Objects Creation$(OKVERT)" || (echo "- $(JAUNE)Objects Creation$(KOROUGE)" && false)
	@ar rc $(NAME) $(OBJ) && echo "- $(JAUNE)Librairie Creation$(OKVERT)" || (echo "- $(JAUNE)Librairie Creation$(KOROUGE)" && false)

.PHONY : clean fclean re all make

clean :
	@rm -rf $(OBJ)
	@echo "- $(JAUNE)Deleted objects$(OKVERT)"

fclean: clean
	@rm -rf $(NAME)
	@echo "- $(JAUNE)Deleted exe$(OKVERT)"

re: fclean all
