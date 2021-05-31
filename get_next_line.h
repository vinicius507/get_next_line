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

typedef enum e_status
{
	ERROR = -1,
	END_OF_FILE,
	NEWLINE,
	NO_NEWLINE,
}	t_status;

int		get_next_line(int fd, char **line);

size_t	ft_strlen(const char *str);

void	kill_save(char **save);

size_t	get_ssize(const char *save);

#endif
