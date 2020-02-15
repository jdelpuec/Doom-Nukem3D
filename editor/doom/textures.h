/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:33:08 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/07 15:12:27 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

#define HEADER_SIZE 54

typedef struct      s_text_tab
{
    char    *path;
    int     *data;
    int     x;
    int     y;
    struct s_text_tab   *next;
    struct s_text_tab   *prev;
}                   t_text_tab;

t_text_tab      handle_textures(char **text_name, int y);
void		    fill_text_tab(int fd, unsigned char *buff_header, t_text_tab *new, int x);
unsigned char	*handle_header(int fd);
void            start_list(t_text_tab **list);
void            list_reach(t_text_tab **list, char *path);
#endif
