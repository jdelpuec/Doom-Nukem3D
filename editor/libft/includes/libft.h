/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <siwarin@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:42:29 by siwarin           #+#    #+#             */
/*   Updated: 2016/04/29 18:48:52 by siwarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

char				**ft_strsplit(char const *s, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnstr(char const *dest, char const *src, size_t n);
char				*ft_strncat(char *dest, char const *src, size_t n);
char				*ft_strstr(char const *dest, char const *src);
char				*ft_strncpy(char *dest, char *src, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin2(char *s1, char *s2, int b);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strcat(char *dest, char const *src);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strrchr(char const *s, int c);
char				*ft_strchr(char const *s, int c);
char				*ft_strtrim(char const *s);
char				*ft_strnew(size_t size);
char				*ft_strdup(char *src);
char				*ft_itoa(int n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_power(int a, int pow);
int					ft_atoi(char const *s);
int					ft_tablen(char **tab);
int					ft_isdigit(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_numlen(int n);
int					ft_root(int a);
size_t				ft_strlcat(char *dest, char const *src, size_t size);
size_t				ft_strlen(char const *s);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_strsplitlst(char const *s, char c);
void				*ft_memccpy(void *dest, void const *src, int c, size_t n);
void				*ft_memmove(void *dest, void const *src, size_t len);
void				*ft_memcpy(void *dest, void const *src, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
void				*ft_memset(void *s, int c, size_t len);
void				*ft_memalloc(size_t size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstaddn(t_list **alst, t_list *new, size_t n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstaddend(t_list **alst, t_list *new);
void				ft_striter(char *s, void (*f)(char *));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(long int n, int fd);
void				ft_bzero(void *s, size_t n);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
void				ft_swap(int *a, int *b);
void				ft_putnbr(long int n);
void				ft_strdel(char **as);
void				ft_memdel(void **ap);
void				ft_strclr(char *s);
void				ft_putchar(char c);

#endif
