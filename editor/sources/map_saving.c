/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_saving.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:01:53 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/17 11:33:26 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"
#include "../includes/list.h"

void	write_first_line(t_editor *edit, t_lst **lst)
{
	edit->saved = 1;
	edit->fd = open("maps/map1", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
	ft_putstr_fd(ft_itoa((*lst)->lst_w->sector_num), edit->fd);
	ft_putstr_fd("\n\n\n\n", edit->fd);
	ft_putstr_fd(ft_itoa((edit->play_x - ((W / 1.5) / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd(ft_itoa((edit->play_y - (H / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd("0.0", edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("0", edit->fd);
	ft_putstr_fd("\n\n\n\n", edit->fd);
	ft_putstr_fd(ft_itoa((*lst)->lst_w->nb_walls), edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("0", edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd(ft_itoa((*lst)->lst_w->walls_h), edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("0", edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("0", edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("0.5", edit->fd);
	ft_putchar_fd('\n', edit->fd);
}

void	sprites_coord(t_sprite *sprite, t_editor *edit)
{
	ft_putstr_fd(ft_itoa((sprite->x - ((W / 1.5) / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd(ft_itoa((sprite->y - (H / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd("5.0", edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd(ft_itoa(sprite->num_sprite), edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("0", edit->fd);
	sprite->next != NULL ? ft_putstr_fd("\n\n\n\n", edit->fd) : 0;
}

void	write_coord(t_editor *edit, t_elem *tmp, t_sprite *sprite, t_lst *l)
{
	ft_putstr_fd(ft_itoa(tmp->num_text), edit->fd);
	ft_putchar_fd(' ', edit->fd);
	ft_putstr_fd("-1\n", edit->fd);
	ft_putstr_fd(ft_itoa((tmp->x1 - ((W / 1.5) / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd(ft_itoa(((tmp->y1 - (H / 2) + 10)) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd(ft_itoa((tmp->x2 - ((W / 1.5) / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0 ", edit->fd);
	ft_putstr_fd(ft_itoa((tmp->y2 - (H / 2) + 10) / 10), edit->fd);
	ft_putstr_fd(".0\n", edit->fd);
	if (l->lst_s->first != NULL && tmp->next == NULL)
	{
		ft_putstr_fd("\n\n\n", edit->fd);
		ft_putstr_fd(ft_itoa(edit->nb_sprites), edit->fd);
		ft_putstr_fd("\n\n\n\n", edit->fd);
		if (sprite->next == NULL)
			sprites_coord(sprite, edit);
		while (sprite->next != NULL)
		{
			sprites_coord(sprite, edit);
			sprite = sprite->next;
			sprite->next == NULL ? sprites_coord(sprite, edit) : 0;
		}
	}
}

void	write_in_file(t_sdl *sdl, t_editor *edit, t_lst **lst)
{
	t_elem		*tmp;
	t_sprite	*sprite;

	if (sdl->e.button.button == SDL_BUTTON_LEFT && sdl->xmouse >= (W / 1.5)
	&& sdl->xmouse <= (W / 1.45) + 190 && sdl->ymouse >= 565
	&& sdl->ymouse <= 595 && edit->saved == 0)
	{
		(*lst)->lst_s->first != NULL ? sprite = (*lst)->lst_s->first : 0;
		if (reverse_list_ornot(lst))
		{
			printf("REVERSED\n");
			*lst = reverse_list(*lst, &tmp);
		}
		tmp = (*lst)->first;
		write_first_line(edit, lst);
		if (tmp->next == NULL)
			write_coord(edit, tmp, sprite, *lst);
		while (tmp->next != NULL)
		{
			write_coord(edit, tmp, sprite, *lst);
			tmp = tmp->next;
			if (tmp->next == NULL)
				write_coord(edit, tmp, sprite, *lst);
		}
		ft_putstr("Map saved.\n");
		hook_keydown(sdl, *lst);
	}
}
