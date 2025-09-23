/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_and_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:04:41 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/22 20:04:51 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"


int	validate_file_extension(char *file)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
	{
		printf("Error\nBad extension!\n");
		return (0);
	}
	return (1);
}


int parse_texture(char *path, char **dest)
{
	int fd;
	char *trimmed;
	
	if (*dest != NULL)
		return (printf("Error\nDuplicate texture!\n"), 0);
	trimmed = ft_strtrim(path, " \n\t");
	if (!trimmed)
		return (printf("Error\nmalloc failed\n"), 0);
	fd = open(trimmed , O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nTexture file not found!\n");
		free(trimmed);
		return (0);
	}
	close(fd);
	*dest = trimmed;
	return (1);
}

int parse_color(char *path, t_color *dest)
{
	char **str;
	int r, g, b;
	
	if ((*dest).r != -1)
		return (printf("Error\nDuplicate texture!\n"), 0);
	str = ft_split(path, ',');
	if (!str || ft_strlen_2d(str) != 3)
		return (printf("Error\nInvalid color format!\n"), free_split(str),0);
	r = ft_atoi(str[0]);
	g = ft_atoi(str[1]);
	b = ft_atoi(str[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (printf("Error\nColor out of range\n"), free_split(str), 0);
	dest->r = r;
	dest->g = g;
	dest->b = b;
	return (1);
}