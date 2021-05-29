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

int	hasbreak(char *buffer, ssize_t size_read)
{
	ssize_t	offset;

	offset = 0;
	while (offset < size_read)
	{
		if (buffer[offset] == '\n')
			return (1);
	}
	return (0);
}
