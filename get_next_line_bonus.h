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

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef enum e_status
{
	ERROR = -1,
	END_OF_FILE,
	NEWLINE,
}	t_status;

int		get_next_line(int fd, char **line);

size_t	ft_strlen(const char *str);

char	*ft_strdup(const char *str);

char	*ft_strjoin(const char *s1, const char *s2);

char	*ft_strchr(const char *s, int c);

char	*linedup(char *save, size_t end);

#endif
