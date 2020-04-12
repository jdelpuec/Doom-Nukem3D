# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 17:18:33 by siwarin           #+#    #+#              #
#    Updated: 2020/02/18 16:49:16 by lubernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCO = $(SRC:.c=.o)

SRC = ft_memalloc.c ft_putendl.c ft_strcmp.c ft_strlen.c ft_strrchr.c \
ft_atoi.c ft_memchr.c ft_putendl_fd.c ft_strcpy.c ft_strmap.c ft_strsplit.c \
ft_bzero.c	ft_memcmp.c	ft_putnbr.c	ft_strdel.c	ft_strmapi.c ft_strstr.c \
ft_isalnum.c ft_memcpy.c ft_putnbr_fd.c	ft_strdup.c	ft_strncat.c ft_strsub.c \
ft_isalpha.c ft_memdel.c ft_putstr.c ft_strequ.c ft_strncmp.c ft_strtrim.c \
ft_isascii.c ft_memmove.c ft_putstr_fd.c ft_striter.c ft_strncpy.c \
ft_tolower.c ft_isdigit.c ft_memset.c ft_strcat.c ft_striteri.c ft_strnequ.c \
ft_toupper.c ft_isprint.c ft_putchar.c ft_strchr.c ft_strjoin.c ft_strnew.c \
ft_itoa.c ft_putchar_fd.c ft_strclr.c ft_strlcat.c ft_strnstr.c ft_memccpy.c \
ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
ft_lstaddend.c ft_lstaddn.c ft_numlen.c ft_strsplitlst.c ft_tablen.c \
ft_swap.c ft_power.c ft_root.c ft_strjoin2.c get_next_line.c \

HEADER = includes \

all: $(NAME)

$(NAME) :
	@gcc $(FLAGS) -c $(SRC) -I $(HEADER)
	@ar rc $(NAME) $(SRCO)

clean:
	@$(RM) $(SRCO)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
