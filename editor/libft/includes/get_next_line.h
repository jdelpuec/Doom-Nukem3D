/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwarin <siwarin@studen.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:08:59 by siwarin           #+#    #+#             */
/*   Updated: 2016/04/20 13:22:39 by siwarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

int get_next_line(const int fd, char **line);

#endif
