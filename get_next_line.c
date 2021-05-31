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

#include "get_next_line.h"

static t_status	check_save(const char *save)
{
	if (save == NULL)
		return (NO_NEWLINE);
	while (*save)
	{
		if (*save == '\n')
			return (NEWLINE);
		save++;
	}
	return (NO_NEWLINE);
}

static void	save_content(char *buf, ssize_t buf_size, char **save)
{
	size_t	i;
	size_t	j;
	char	*temp;
	size_t	m_size;

	m_size = buf_size;
	if (*save != NULL)
		m_size += ft_strlen(*save);
	temp = malloc(m_size + 1);
	if (temp == NULL)
	{
		kill_save(save);
		return ;
	}
	i = 0;
	j = 0;
	while (*save != NULL && (*save)[j])
		temp[i++] = (*save)[j++];
	j = 0;
	while (j < (size_t)buf_size)
		temp[i++] = buf[j++];
	temp[i] = '\0';
	if (*save != NULL)
		free(*save);
	*save = temp;
}

static void	get_line(char **save, char **line, t_status status)
{
	size_t	size;
	size_t	offset;

	if (status == END_OF_FILE && *save == NULL)
	{
		kill_save(save);
		*line = malloc(1);
		if (*line == NULL)
			return ;
		(*line)[0] = '\0';
		return ;
	}
	size = 0;
	while ((*save)[size] && (*save)[size] != '\n')
		size++;
	*line = malloc(size + 1);
	if (*line == NULL)
		return ;
	offset = -1;
	while (++offset < size)
		(*line)[offset] = (*save)[offset];
	(*line)[offset] = '\0';
}

static void	reset_content(char **save)
{
	char	*temp;
	size_t	m_size;
	size_t	offset;
	char	*s_save;

	if (*save == NULL)
		return ;
	m_size = get_ssize(*save);
	temp = malloc(m_size + 1);
	if (temp == NULL)
	{
		kill_save(save);
		return ;
	}
	s_save = *save;
	while (*s_save && *s_save != '\n')
		s_save++;
	offset = 0;
	while (offset < m_size)
		temp[offset++] = *++s_save;
	temp[offset] = '\0';
	kill_save(save);
	*save = temp;
}

int	get_next_line(int fd, char **line)
{
	ssize_t		size_read;
	static char	*save;
	char		buf[BUFFER_SIZE];
	t_status	status;

	status = check_save(save);
	while (status == NO_NEWLINE)
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read == -1)
		{
			kill_save(&save);
			return (ERROR);
		}
		if (size_read == 0)
			break ;
		save_content(buf, size_read, &save);
		if (save == NULL)
			return (ERROR);
		status = check_save(save);
	}
	get_line(&save, line, status);
	reset_content(&save);
	return (status);
}
