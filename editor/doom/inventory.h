/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubernar <lubernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:38:16 by lubernar          #+#    #+#             */
/*   Updated: 2020/02/08 14:09:53 by lubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef struct		s_inventory
{
	char	*inventory;
	int		inventory_display[4];
}					t_inventory;
