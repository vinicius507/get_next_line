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

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	concat_save(char *save, char *old, char *new, ssize_t limit)
{
	if (old != NULL)
	{
		while (*old)
			*save++ = *old++;
	}
	while (limit-- && *new)
		*save++ = *new++;
	*save = '\0';
}

size_t	find_break(char *str)
{
	size_t	offset;

	offset = 0;
	while (str[offset])
	{
		if (str[offset] == '\n')
			return (offset);
		offset++;
	}
	return (offset);
}
