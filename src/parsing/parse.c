/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:53:36 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 12:01:01 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	int	fd;
    
    if (!validate_file_extension(filedata))
		return (0);
	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nopening file\n"), 0);
    if (!parse_configurations(game, fd))
		return (0);
	if (!parse_map(game, fd))
		return (0);
    close (fd);
    return (1);
}
