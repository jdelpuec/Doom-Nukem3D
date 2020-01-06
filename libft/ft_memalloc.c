/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:49:31 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 15:59:41 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*s;

	s = ((void*)malloc(sizeof(void) * size));
	if (s == NULL)
		return (NULL);
	else
		return (ft_memset(s, 0, size));
}
