/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:25:37 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 12:26:06 by moirhira         ###   ########.fr       */
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