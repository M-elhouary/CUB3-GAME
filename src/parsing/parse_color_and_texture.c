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

int validate_file_extension(char *file, char *extension)
{
	char *search;

	search = ft_strrchr(file, '.');
	if (!search || ft_strcmp(search, extension) != 0)
	{
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
	if (!trimmed || *trimmed == '\0')
	{
		free(trimmed);
		return (printf("Error\nTexture path is missing or invalid.\n"), 0);
	}
	if (!validate_file_extension(trimmed, ".xpm"))
	{
		free(trimmed);
		return (printf("Error\nTexture file must be a .xpm file!\n"), 0);
	}
	fd = open(trimmed, O_RDONLY);
	if (fd == -1)
	{
		free(trimmed);
		printf("Error\nCannot open texture file!\n");
		return (0);
	}
	close(fd);
	*dest = trimmed;
	free(trimmed);
	return (1);
}

int parse_color(char *path, t_color *dest)
{
	char **str;
	char *trimmed;
	int colors[3], i;

	if ((*dest).r != -1)
		return (printf("Error\nDuplicate color definition!\n"), 0);
	str = ft_split(path, ',');
	if (!str || ft_strlen_2d(str) != 3)
		return (printf("Error\nInvalid color format!\n"), free_split(str), 0);
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(str[i], " \t\n");
		if (!is_all_digits(trimmed))
		{
			free(trimmed);
			free_split(str);
			return (printf("Error\nColor value contains non-digit characters.\n"), 0);
		}
		colors[i] = ft_atoi(trimmed);
		free(trimmed);
		if (colors[i] < 0 || colors[i] > 255)
			return (printf("Error\nColor out of range\n"), free_split(str), 0);
		i++;
	}
	free_split(str);
	dest->r = colors[0];
	dest->g = colors[1];
	dest->b = colors[2];
	return (1);
}
