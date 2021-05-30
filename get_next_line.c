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

#include <stdio.h>
#include "get_next_line.h"

static size_t	hasbreak(char *save)
{
	ssize_t	offset;

	offset = 0;
	while (save[offset])
	{
		if (save[offset] == '\n')
			return (1);
		offset++;
	}
	return (0);
}

static char	*save_content(char *save, char *buffer, ssize_t size_read)
{
	char	*temp;
	size_t	m_size;

	m_size = size_read + 1;
	if (save != NULL)
		m_size += ft_strlen(save);
	temp = malloc(m_size);
	if (temp == NULL)
		return (NULL);
	concat_save(temp, save, buffer, size_read);
	if (save != NULL)
	{
		free(save);
		save = NULL;
	}
	return (temp);
}

static char	*get_line(char **save)
{
	size_t	len;
	char	*line;
	char	*temp;
	size_t	limit;
	size_t	offset;

	len = ft_strlen(*save);
	limit = find_break(*save) + 1;
	line = malloc(limit);
	if (line == NULL)
		return (NULL);
	offset = 0;
	while ((*save)[offset] && (*save)[offset] != '\n')
	{
		line[offset] = (*save)[offset];
		offset++;
	}
	line[offset] = '\0';
	temp = save_content(NULL, *save + limit, len - limit + 1);
	free(*save);
	*save = temp;
	return (line);
}

int	get(char **save, char **line, size_t size_read)
{
	if (hasbreak(*save) || size_read < BUFFER_SIZE)
	{
		*line = get_line(save);
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	ssize_t			size_read;
	static char		*save[1025];
	char			buffer[BUFFER_SIZE];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (save[fd] != NULL && get(&(save[fd]), line, BUFFER_SIZE))
		return (1);
	size_read = read(fd, buffer, BUFFER_SIZE);
	while (size_read > 0)
	{
		save[fd] = save_content(save[fd], buffer, size_read);
		if (save[fd] == NULL)
			return (-1);
		if (save[fd] != NULL && get(&(save[fd]), line, size_read))
			return (1);
		size_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (size_read == -1)
		return (-1);
	return (0);
}
