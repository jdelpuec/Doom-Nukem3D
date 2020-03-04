/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:12:50 by cduverge          #+#    #+#             */
/*   Updated: 2020/03/04 16:50:03 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	mouse_button_down(t_sdl *sdl, t_editor *edit)
{
	if (sdl->e.type == SDL_MOUSEBUTTONDOWN)
	{
		textures_area(sdl, edit);
		if (edit->nb_clic >= 2 && sdl->e.type == SDL_MOUSEBUTTONDOWN
		&& sdl->xmouse <= (W / 1.5) - 11 && sdl->xmouse >= 11
		&& sdl->ymouse >= 11 && sdl->ymouse <= H - 11)
			edit->nb_clic++;
		if (sdl->e.motion.x >= (W / 1.45) && sdl->e.motion.x
		<= (W / 1.45) + 30 && sdl->e.motion.y >= 450
		&& sdl->e.motion.y <= 480 && edit->nb_clic == 0)
			edit->player_selected = 1;
		if (sdl->e.motion.x >= (W / 1.45) + 520 && sdl->e.motion.x
		<= (W / 1.45) + 550 && sdl->e.motion.y >= 65 && sdl->e.motion.y
		<= 80 && edit->walls_h < 99 && edit->nb_clic == 0)
			edit->walls_h += 3;
		if (sdl->e.motion.x >= (W / 1.45) + 520 && sdl->e.motion.x
		<= (W / 1.45) + 550 && sdl->e.motion.y >= 80 && sdl->e.motion.y
		<= 95 && edit->walls_h > 32 && edit->nb_clic == 0)
			edit->walls_h -= 3;
	}
}

void	editor(t_sdl *sdl, t_lst **lst, t_line *line)
{
	t_keyboard	k;
	t_editor	edit;

	init_edit(&edit);
	init_textures(&edit);
	k.state = SDL_GetKeyboardState(NULL);
	ft_init(sdl);
	while (sdl->running)
	{
		while (SDL_PollEvent(&sdl->e))
		{
			if (k.state[SDL_SCANCODE_ESCAPE] == 1)
				hook_keydown(sdl, *lst);
			SDL_GetGlobalMouseState(&sdl->xmouse, &sdl->ymouse);
			sdl->xmouse = sdl->e.motion.x;
			sdl->ymouse = sdl->e.motion.y;
			mouse_button_down(sdl, &edit);
			edit.texture_choosen != 0 ? clic(sdl, line, &edit, lst) : 0;
		}
		editdraw(sdl, &edit, line, lst);
		SDL_UpdateWindowSurface(sdl->win);
		SDL_FreeSurface(sdl->ren);
		if (sdl->e.type == SDL_QUIT)
			hook_keydown(sdl, *lst);
	}
}

void	pixel(t_sdl *sdl, int x, int y)
{
	if (x < 0 || x >= W || y < 0 || y >= H)
		return ;
	*((int *)sdl->ren->pixels + (y * W + x)) = sdl->color;
}

int		main(void)
{
	t_sdl		sdl;
	t_lst		*lst;
	t_line		line;
	t_elem		e;
	t_sprite	sprite;

	if (!(lst = malloc(sizeof(t_lst))))
		return (0);
	if (!(lst->lst_s = malloc(sizeof(t_lst_sprite))))
		return (0);
	init(lst, &e);
	init_sprite(lst->lst_s);
	sprite = init_sprites();
	editor(&sdl, &lst, &line);
	return (0);
}
