/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:11:08 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 16:00:58 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dest, void const *src, size_t len)
{
	unsigned char	temp[len];

	ft_memcpy(temp, src, len);
	ft_memcpy(dest, temp, len);
	return (dest);
}
