/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelpuec <jdelpuec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:29:52 by jdelpuec          #+#    #+#             */
/*   Updated: 2020/02/10 11:31:04 by jdelpuec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

int					*int_malloc(char *name, int size);
char				*sting_malloc(char *name, int size);
char				**tab_malloc(char *name, int size);
unsigned char		*unsigned_char_malloc(char *name, int size);
#endif