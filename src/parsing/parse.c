/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:53:36 by moirhira          #+#    #+#             */
/*   Updated: 2026/01/19 20:32:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_configurations(t_game *game, int fd, char **f_line)
{
	char	*line;
	char	*trimmed;
	int		parsed;

	parsed = 0;
	line = get_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, " \n\t");
		if (parsed == 6)
		{
			*f_line = line;
			return (1);
		}
		if (!handle_config_line(game, trimmed, &parsed))
			return (0);
		line = get_line(fd);
	}
	if (parsed != 6)
		return (printf("Error\nMissing configuration element\n"), 0);
	return (1);
}

int	parse_map(t_game *game, int fd, char *first_line)
{
	game->map->map_arr = NULL;
	if (!read_map_lines(game, fd, first_line))
		return (0);
	return (validate_map(game));
}

int	parse(t_game *game, char *filedata)
{
	int		fd;
	char	*f_line;

	if (!validate_file_extension(filedata, ".cub"))
		return (printf("Error\nBad extension!\n"), 0);
	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 0);
	if (is_dir(filedata))
	{
		printf("Error\nArgument is a derctory!\n");
		return (close(fd), 0);
	}
	f_line = NULL;
	if (!parse_configurations(game, fd, &f_line))
		return (close(fd), 0);
	if (f_line && f_line[0] != '1' && f_line[0] != '\n')
	{
		printf("Error\nDuplicate configuration or invalid char!\n");
		return (close(fd), 0);
	}
	if (!parse_map(game, fd, f_line))
		return (close(fd), 0);
	if (!parse_objects(game, fd, NULL))
		return (close(fd), 0);
	close(fd);
	return (1);
}
