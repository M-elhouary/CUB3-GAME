/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:53:36 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/22 15:27:08 by moirhira         ###   ########.fr       */
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


int parse_configurations(t_game *game, int fd)
{
	char *line;
	char *trimmed;
	int parsed = 0;
	
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, " \n\t");
		if (!*trimmed)
		{
			free(trimmed);
			free(line);
			continue;
		}
		if (ft_strncmp("NO ", line, 3) == 0)
			parsed += parse_texture(line + 3, &game->tex_paths[0]);
		else if (ft_strncmp("SO ", line, 3) == 0)
			parsed += parse_texture(line + 3, &game->tex_paths[1]);
		else if (ft_strncmp("WE ", line, 3) == 0)
			parsed += parse_texture(line + 3, &game->tex_paths[2]);
		else if (ft_strncmp("EA ", line, 3) == 0)
			parsed += parse_texture(line + 3, &game->tex_paths[3]);
		else if ((ft_strncmp("F ", line, 2) == 0))
			parsed += parse_color(line + 2, &game->floor_color);
		else if ((ft_strncmp("C ", line, 2) == 0))
			parsed += parse_color(line + 2, &game->ceiling_color);
		else
		{
			free(trimmed);
			free(line);
			return (printf("Error\nInvalid configuration!\n"), 0);
		}
		free(trimmed);
		free(line);
		if (parsed == 6)
			return (1);
	}
	return (printf("Error\nMissing configuration element\n"), 0);
}


int	parse(t_game *game, char *filedata)
{
    int	i;
	int	fd;
    
    if (!validate_file_extension(filedata))
		return (0);
	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nopening file\n"), 0);
    parse_configurations(game, fd);
	printf("SO-> %s\n", game->tex_paths[0]);
	printf("SO-> %s\n", game->tex_paths[1]);
	printf("SO-> %s\n", game->tex_paths[2]);
	printf("SO-> %s\n", game->tex_paths[3]);
	printf("floor -> %d\n", game->floor_color.r);
	printf("cieling -> %d\n", game->ceiling_color.r);
    close (fd);
    return (1);
}