/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:49:37 by cduverge          #+#    #+#             */
/*   Updated: 2018/11/30 14:53:55 by cduverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;

	if (!(lst) || !(f))
		return (NULL);
	if (!(res = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	res = f(lst);
	if (lst->next)
		res->next = ft_lstmap(lst->next, f);
	return (res);
}
