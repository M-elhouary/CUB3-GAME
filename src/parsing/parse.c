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

char *get_arg(char *line)
{
    int i = 0;

    while (line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    return (&line[i]);
}

int parse_configurations(t_game *game, int fd, char **f_map_line)
{
	char *line;
	char *trimmed;
	int parsed = 0;
	
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, " \n\t");
		free(line);
		if (!trimmed)
            return (printf("Error\nMalloc failed\n"), 0);
		if (*trimmed == '\0')
		{
			free(trimmed);
			continue;
		}
		if (parsed == 6)
		{
			*f_map_line = trimmed;
			return (1);
		}
		if (ft_strncmp("NO ", trimmed, 3) == 0)
			parsed += parse_texture(get_arg(trimmed), &game->tex_paths[0]);
		else if (ft_strncmp("SO ", trimmed, 3) == 0)
			parsed += parse_texture(get_arg(trimmed), &game->tex_paths[1]);
		else if (ft_strncmp("WE ", trimmed, 3) == 0)
			parsed += parse_texture(get_arg(trimmed), &game->tex_paths[2]);
		else if (ft_strncmp("EA ", trimmed, 3) == 0)
			parsed += parse_texture(get_arg(trimmed), &game->tex_paths[3]);
		else if ((ft_strncmp("F ", trimmed, 2) == 0))
			parsed += parse_color(get_arg(trimmed), &game->floor_color);
		else if ((ft_strncmp("C ", trimmed, 2) == 0))
			parsed += parse_color(get_arg(trimmed), &game->ceiling_color);
		else
		{
			free(trimmed);
			return (printf("Error\nInvalid configuration!\n"), 0);
		}
		free(trimmed);
	}
	if (parsed != 6)
		return (printf("Error\nMissing configuration element\n"), 0);
	f_map_line = NULL;
	return (1);
}


int	parse(t_game *game, char *filedata)
{
	int	fd;
	char *f_line;
    
    if (!validate_file_extension(filedata))
		return(printf("Error\nBad extension!\n"), 0);
	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 0);
	if (is_dir(filedata))
		return (printf("Error\nArgument is a derctory!\n"), close(fd),0);
    if (!parse_configurations(game, fd, &f_line))
		return (close(fd), 0);
	if (!parse_map(game, fd, f_line))
		return (close(fd), 0);
    close (fd);
    return (1);
}
