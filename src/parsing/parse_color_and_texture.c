/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_and_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:04:41 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/12 14:07:47 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_file_extension(char *file, char *extension)
{
	char	*search;

	search = ft_strrchr(file, '.');
	if (!search || ft_strcmp(search, extension) != 0)
	{
		return (0);
	}
	return (1);
}

int	parse_texture(char *path, char **dest)
{
	int		fd;
	char	*trimmed;

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
		return (printf("Error\nCannot open texture file!\n"), 0);
	}
	close(fd);
	*dest = trimmed;
	return (1);
}

int	rgb_to_int(t_color *c)
{
	return ((c->r << 16) | (c->g << 8) | c->b);
}

int	validate_color_values(char **str, int *colors)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(str[i], " \t\n");
		if (!is_all_digits(trimmed))
		{
			free(trimmed);
			free_split(str);
			return (printf("Error\nColor value contains non-digit characters.\n"),
				0);
		}
		colors[i] = ft_atoi(trimmed);
		free(trimmed);
		if (colors[i] < 0 || colors[i] > 255)
			return (free_split(str), printf("Error\nColor out of range\n"), 0);
		i++;
	}
	return (1);
}

int	parse_color(char *path, t_color *dest)
{
	char	**str;
	int		colors[3];

	if ((*dest).r != -1)
		return (printf("Error\nDuplicate color definition!\n"), 0);
	str = ft_split(path, ',');
	if (!str || ft_strlen_2d(str) != 3)
	{
		printf("Error\nInvalid color format!\n");
		free_split(str);
		return (0);
	}
	if (!validate_color_values(str, colors))
		return (0);
	free_split(str);
	dest->r = colors[0];
	dest->g = colors[1];
	dest->b = colors[2];
	dest->hex_color = rgb_to_int(dest);
	return (1);
}
