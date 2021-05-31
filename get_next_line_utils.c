/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:57:44 by vgoncalv          #+#    #+#             */
/*   Updated: 2021/05/29 16:57:44 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	kill_save(char **save)
{
	if (*save != NULL)
	{
		free(*save);
		*save = NULL;
	}
}

size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (*end)
		end++;
	return (end - str);
}

size_t	get_ssize(const char *save)
{
	size_t	size;

	while (*save && *save != '\n')
		save++;
	if (*save)
		save += 1;
	size = 0;
	while (save[size])
		size++;
	return (size);
}
