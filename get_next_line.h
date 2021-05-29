/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:56:22 by vgoncalv          #+#    #+#             */
/*   Updated: 2021/05/29 16:56:22 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# if !defined(BUFFER_SIZE)
#  define BUFFER_SIZE 1024
# endif

int	get_next_line(int fd, char **line);

int	hasbreak(char *buffer, ssize_t size_read);

#endif
