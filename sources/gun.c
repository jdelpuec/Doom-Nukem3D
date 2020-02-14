/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:53:22 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/14 16:15:32 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "raycasting.h"

// void    anim_gun(t_text_tab *gun_anim, t_win *w,  int j)
// {
//    if (w->e.type == SDL_MOUSEBUTTONDOWN &&  w->pressed == 0
//         && inv->nb_bullet > 0)
// 	{
//         inv->nb_bullet--;
//         w->pressed = 1;
//         gun_anim = gun_anim->next;
//         gun_anim->w = 240;
//         gun_anim->h = 240;
//         j != 0 ? display_l((WIN_W / 2), (WIN_H) - 240, w, *gun_anim) : 0;
//         anim = 1;
//         anim = 0;
//     }
//     else if (j != 0 && anim != 1)
//     {
//         w->pressed = 0;
//         display_l((WIN_W / 2), (WIN_H) - 240, w, *gun_anim);
//     }

// }
void    reload_gun(t_text_tab *reload_anim, t_ray *r, t_win *w)
{
    char        **reload;
    static int  j;
    
     if (j == 0)
    {
        reload = (char**)malloc(sizeof(char*) * 4);
        reload[0] = "ress/gun4.bmp";
        reload[1] = "ress/gun5.bmp";
        reload[2] = "ress/gun2.bmp";
        reload[3] = NULL;
        *reload_anim = handle_textures(reload, 0);
        free(reload);
        j = 1;
    }
    reload_anim->w = 240;
    reload_anim->h = 240;
    if (SDL_GetTicks() - w->old_t > 1 && SDL_GetTicks() - w->old_t < 300)
        display_l((WIN_W / 2), (WIN_H) - 240, w, *reload_anim);
    else if (SDL_GetTicks() - w->old_t > 300 && SDL_GetTicks() - w->old_t < 700)
    {
        reload_anim = reload_anim->next;
        reload_anim->w = 240;
        reload_anim->h = 240;
        display_l((WIN_W / 2), (WIN_H) - 240, w, *reload_anim);
    }
    else if (SDL_GetTicks() - w->old_t > 700)
    {
        reload_anim = reload_anim->next;
        reload_anim->w = 240;
        reload_anim->h = 240;
        display_l((WIN_W / 2), (WIN_H) - 240, w, *reload_anim);
        if (SDL_GetTicks() - w->old_t > 1000)
        {
            w->reload = 0;
            r->inv.anim = 0;
            w->fired = 0;
        }
    }
}


t_text_tab  init_gun()
{
    char        **gun;
    static int  j;
    t_text_tab gun_anim;
    
    if (j == 0)
    {
        gun = (char**)malloc(sizeof(char*) * 3);
        gun[0] = "ress/gun1.bmp";
        gun[1] = "ress/gun2.bmp";
        gun[2] = NULL;
        gun_anim = handle_textures(gun, 0);
        free(gun);
        j = 1;
    }
    gun_anim.w = 240;
    gun_anim.h = 240;
    return (gun_anim);
}

void    fire_gunshot(t_win *w, t_text_tab *gun_anim)
{
    if (SDL_GetTicks() - w->old_t_f < 300)
    {
        gun_anim = gun_anim->next;
        gun_anim->w = 240;
        gun_anim->h = 240;
        display_l((WIN_W / 2), (WIN_H) - 240, w, *gun_anim);
    }
    if (SDL_GetTicks() - w->old_t_f > 300)
    {
        w->fired = 0;
    }
}