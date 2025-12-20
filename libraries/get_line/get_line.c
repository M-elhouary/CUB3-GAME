/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:57:04 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/11 20:54:45 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

char	*my_strdup(char *src)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	len = calclen(src);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

void	ft_strcat(char *dest, const char *src)
{
	int	dest_len;
	int	i;

	dest_len = calclen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
}

char	*append_to_buffer(char *buffer, char *buf, int readed)
{
	char	*temp;

	if (!buffer)
		buffer = my_strdup(buf);
	else
	{
		temp = buffer;
		buffer = malloc(calclen(temp) + readed + 1);
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
		ft_copy(buffer, temp);
		ft_strcat(buffer, buf);
		free(temp);
	}
	return (buffer);
}

char	*readfromfd(int fd, char *buffer)
{
	char	*buf;
	int		readed;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	readed = read(fd, buf, BUFFER_SIZE);
	while (readed > 0)
	{
		if (readed == -1)
		{
			free(buf);
			free(buffer);
			return (NULL);
		}
		buf[readed] = '\0';
		buffer = append_to_buffer(buffer, buf, readed);
		if (find_newline(buffer, '\n'))
			break ;
		readed = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (buffer);
}


static char *buffer = NULL;

char *get_line(int fd)
{
	char *line;

	if (!find_newline(buffer, '\n'))
	{
		buffer = readfromfd(fd, buffer);
		if (!buffer)
			return (NULL);
	}
	line = separate_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}

void free_get_line_buffer(void)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}
