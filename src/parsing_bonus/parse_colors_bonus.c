/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:04:41 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 22:29:35 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	rgb_to_int(t_color *c)
{
	return ((c->r << 16) | (c->g << 8) | c->b);
}

static int	has_valid_color_format(char *path)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	if (!path || *path == '\0')
		return (0);
	while (path[i])
	{
		if (path[i] == ',')
		{
			commas++;
			if (path[i + 1] == ',')
				return (0);
		}
		i++;
	}
	if (commas != 2)
		return (0);
	return (1);
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
			return (printf("Error\nColor value contains non-digit characters.\n"),
				0);
		}
		colors[i] = ft_atoi(trimmed);
		if (colors[i] < 0 || colors[i] > 255)
			return (printf("Error\nColor out of range\n"), 0);
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
	if (!has_valid_color_format(path))
		return (printf("Error\nInvalid color format!\n"), 0);
	str = ft_split(path, ',');
	if (!str || ft_strlen_2d(str) != 3)
	{
		printf("Error\nInvalid color format!\n");
		return (0);
	}
	if (!validate_color_values(str, colors))
		return (0);
	dest->r = colors[0];
	dest->g = colors[1];
	dest->b = colors[2];
	dest->hex_color = rgb_to_int(dest);
	return (1);
}
