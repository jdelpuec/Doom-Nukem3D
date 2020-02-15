/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:51:17 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/06 10:14:50 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Doom_Nukem.h"

void	write_text2(t_sdl *sdl, t_editor *edit)
{
	char	*tmp;

	tmp = ft_itoa(edit->walls_h);
	sdl->mes = TTF_RenderText_Solid(sdl->font, "save map", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45), 565, sdl->mes, sdl->ren);
	sdl->mes = TTF_RenderText_Solid(sdl->font, "/ ceiling height : ", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45) + 180, 65, sdl->mes, sdl->ren);
	sdl->mes = TTF_RenderText_Solid(sdl->font, tmp, sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45) + 470, 65, sdl->mes, sdl->ren);
	free(tmp);
}

void	write_text(t_sdl *sdl, t_editor *edit)
{
	sdl->mes = TTF_RenderText_Solid(sdl->font, "Map editor", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45), 20, sdl->mes, sdl->ren);
	sdl->mes = TTF_RenderText_Solid(sdl->font, "Textures", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45), 65, sdl->mes, sdl->ren);
	sdl->mes = TTF_RenderText_Solid(sdl->font, "Items", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45), 165, sdl->mes, sdl->ren);
	sdl->mes = TTF_RenderText_Solid(sdl->font, "Ennemies", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45), 265, sdl->mes, sdl->ren);
	sdl->mes = TTF_RenderText_Solid(sdl->font, "Player", sdl->fc);
	if (sdl->mes == NULL)
		return ;
	apply_surface((W / 1.45), 400, sdl->mes, sdl->ren);
	write_text2(sdl, edit);
}
