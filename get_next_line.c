/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:56:03 by vgoncalv          #+#    #+#             */
/*   Updated: 2021/05/29 16:56:03 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: remind to delete stdio
#include <stdio.h>
#include "get_next_line.h"

static int	check_save(char *save)
{
	size_t	len;

	if (!save)
		return (0);
	len = ft_strlen(save);
	if (!len)
		return (1);
	while (*save)
	{
		if (*save == '\n')
			return (1);
		save++;
	}
	return (0);
}

static int	get_line(char *save, char **line)
{
	size_t	len;
	size_t	offset;

	if (!check_save(save))
		return (0);
	len = get_line_len(save);
	*line = malloc(len + 1);
	if (*line == NULL)
		return (-1);
	offset = 0;
	while (offset < len)
	{
		(*line)[offset] = save[offset];
		offset++;
	}
	(*line)[offset] = '\0';
	return (1);
}

static int	save_content(char **save, char *content, ssize_t size_read)
{
	char	*temp;
	ssize_t	m_size;

	m_size = size_read + 1;
	if (*save != NULL)
		m_size += ft_strlen(*save);
	temp = malloc(m_size);
	if (temp == NULL)
		return (0);
	concat_save(temp, *save, content, size_read);
	if (*save != NULL)
		free(*save);
	*save = temp;
	return (1);
}

static void	reset_content(char **save)
{
	char	*temp;
	size_t	offset;
	size_t	save_size;

	offset = get_line_len(*save);
	save_size = ft_strlen(*save);
	if (offset == save_size)
		return ;
	temp = malloc(save_size - offset);
	if (temp == NULL)
		return ;
	concat_save(temp, NULL, (*save) + offset + 1, save_size - offset);
	if (*save != NULL)
		free(*save);
	*save = temp;
}

int	get_next_line(int fd, char **line)
{
	int			hasline;
	ssize_t		size_read;
	static char	*save[1024];
	char		buffer[BUFFER_SIZE];

	hasline = 0;
	while (!hasline)
	{
		hasline = get_line(save[fd], line);
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read == -1 || hasline == -1 || !save_content(&(save[fd]),
				buffer, size_read))
			return (-1);
		if (hasline == 1)
		{
			reset_content(&(save[fd]));
			return (!!size_read);
		}
	}
	return (0);
}
