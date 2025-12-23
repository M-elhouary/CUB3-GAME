/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:25:37 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/22 17:18:16 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_file_extension(char *file, char *extension)
{
	char	*search;

	if (!file || !extension)
		return (0);
	search = ft_strrchr(file, '.');
	if (!search || ft_strcmp(search, extension) != 0)
	{
		return (0);
	}
	return (1);
}

int	parse_texture(char *path, char **dest)
{
	char	*trimmed;
	int		fd;

	if (*dest != NULL)
		return (printf("Error\nDuplicate texture!\n"), 0);
	trimmed = ft_strtrim(path, " \n\t");
	if (!trimmed || *trimmed == '\0')
	{
		printf("Error\nTexture path is missing or invalid.\n");
		return (0);
	}
	if (!validate_file_extension(trimmed, ".xpm"))
	{
		printf("Error\nTexture file must be a .xpm file!\n");
		return (0);
	}
	fd = open(trimmed, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open texture file!\n");
		return (0);
	}
	close(fd);
	*dest = trimmed;
	return (1);
}
