/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:38:16 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/15 18:43:46 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVENTORY_H
# define INVENTORY_H

typedef struct		s_inventory
{
	char	**inventory;
	int		inventory_display[4];
}					t_inventory;

typedef struct		s_parsing_sprite
{
	int						x;
	int						y;
	int						z;
	int						num_sprite;
	int						nb_maillon;
	int						pickable;
	int						nb_noodles;
	struct s_parsing_sprite	*next;
	struct s_parsing_sprite	*prev;
}					t_parsing_sprite;

#endif