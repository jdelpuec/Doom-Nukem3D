/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:53:22 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/12 17:12:37 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"

// void    anim_gun(t_text_tab *gun_anim, t_win *w)
// {
//       if (w->e.type == SDL_MOUSEBUTTONDOWN && w->pressed == 0)
// 	{
//         w->old_t = SDL_GetTicks();
//         w->pressed = 1;
//         gun_anim = gun_anim->next;
//         gun_anim->w = 240;
//         gun_anim->h = 240;
//         j != 0 ? display((WIN_W / 2) - 120, (WIN_H) - 240, w, *gun_anim) : 0;
//         anim = 1;
//     }
//     if (w->pressed == 1)
//     {
//         if (SDL_GetTicks() - w->old_t >= 1)
//         {
//             anim = 0;
//             w->pressed = 0;
//         }
//     }

// }

void    init_gun(t_win *w, t_text_tab *gun_anim)
{
    char        **gun;
    static int  j;
    static int  anim;
    
    if (j == 0)
    {
        gun = (char**)malloc(sizeof(char*) * 3);
        gun[0] = "ress/gun1.bmp";
        gun[1] = "ress/gun2.bmp";
        gun[2] = NULL;
        *gun_anim = handle_textures(gun, 0);
        free(gun);
        j = 1;
    }
    gun_anim->w = 240;
    gun_anim->h = 240;
    if (w->e.type == SDL_MOUSEBUTTONDOWN &&  w->pressed == 0)
	{
    //     w->old_t = SDL_GetTicks();
        w->pressed = 1;
        gun_anim = gun_anim->next;
        gun_anim->w = 240;
        gun_anim->h = 240;
        j != 0 ? display((WIN_W / 2) - 120, (WIN_H) - 240, w, *gun_anim) : 0;
        anim = 1;
        anim = 0;
    }
    else if (j != 0 && anim != 1)
    {
        w->pressed = 0;
        display((WIN_W / 2) - 120, (WIN_H) - 240, w, *gun_anim);
    }
}