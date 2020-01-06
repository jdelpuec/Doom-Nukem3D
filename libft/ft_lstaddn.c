/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonafi <ebonafi@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:19:58 by ebonafi           #+#    #+#             */
/*   Updated: 2016/04/07 15:58:45 by ebonafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstaddn(t_list **alst, t_list *new, size_t n)
{
	t_list *lst;

	lst = *alst;
	while (n && lst)
	{
		lst = lst->next;
		n--;
	}
	if (!lst && n > 0)
		return ;
	lst = new;
}
