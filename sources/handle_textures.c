/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:44:05 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/19 15:52:20 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "textures.h"
#include "malloc.h"

unsigned char	*handle_header(int fd)
{
	unsigned char	*buff_header;
	unsigned char	*buff_skip;
	int				color_start;

	buff_header = unsigned_char_malloc("buff_header", HEADER_SIZE);
	read(fd, buff_header, HEADER_SIZE);
	color_start = (buff_header[10] + (buff_header[11] << 8)
		+ (buff_header[12] << 16) + (buff_header[13] << 24)) - 54;
	buff_skip = unsigned_char_malloc("buff_skip", color_start);
	if (read(fd, buff_skip, color_start) == -1)
		return (NULL);
	free(buff_skip);
	return (buff_header);
}

void			fill_text_tab(int fd, unsigned char *buff_header,
													t_text_tab *new, int x)
{
	unsigned char	*buff_color;
	short			bpp;
	int				y;
	int				length;

	new->tex_w = (buff_header[18] + (buff_header[19] << 8)
			+ (buff_header[20] << 16) + (buff_header[21] << 24));
	bpp = (buff_header[28] + (buff_header[29] << 8)) / 8;
	length = (buff_header[34] + (buff_header[35] << 8) + (buff_header[36] << 16)
		+ (buff_header[37] << 24)) / bpp;
	buff_color = unsigned_char_malloc("buff_color", length * bpp);
	new->data = int_malloc("new->data", length);
	read(fd, buff_color, length * bpp);
	y = length - 1;
	while (++x < length)
	{
		if (bpp == 4)
			new->data[y] = buff_color[x * 4] + (buff_color[x * 4 + 1] << 8)
			+ (buff_color[x * 4 + 2] << 16) + (0 << 24);
		else if (bpp == 3)
			new->data[y] = buff_color[x * 3] + (buff_color[x * 3 + 1] << 8)
			+ (buff_color[x * 3 + 2] << 16) + (0 << 24);
		y--;
	}
	free(buff_color);
}

void			add_list(t_text_tab **last)
{
	t_text_tab *new;

	if (!(new = (t_text_tab *)malloc(sizeof(t_text_tab))))
	{
		ft_putendl("Malloc error (new)");
		return ;
	}
	new->next = NULL;
	new->prev = *last;
	(*last)->next = new;
	*last = (*last)->next;
}

t_text_tab		*create_list(t_text_tab *list_text)
{
	list_text->next = NULL;
	list_text->prev = NULL;
	return (list_text);
}

t_text_tab		handle_textures(char **text_name, int y)
{
	unsigned char	*buff_header;
	t_text_tab		list_text;
	t_text_tab		*last;
	int				fd;

	last = create_list(&list_text);
	while (text_name[++y] != NULL)
	{
		y != 0 ? add_list(&last) : 0;
		fd = open(text_name[y], O_RDONLY | O_NOFOLLOW);
		last->id = y;
		last->path = ft_strdup(text_name[y]);
		if (fd == -1)
		{
			last->id = -1;
			return (*last);
		}
		buff_header = handle_header(fd);
		fill_text_tab(fd, buff_header, last, -1);
		close(fd);
		free(buff_header);
	}
	while (last->prev != NULL)
		last = last->prev;
	return (*last);
}
