/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:53:36 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/12 14:02:18 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_config_line(t_game *game, char *line, char *trimmed, int *parsed)
{
	if (*trimmed == '\0')
	{
		free(trimmed);
		free(line);
		return (1);
	}
	if (!process_config_line(game, trimmed, parsed))
	{
		free(trimmed);
		free(line);
		return (printf("Error\nInvalid configuration!\n"), 0);
	}
	free(trimmed);
	free(line);
	return (1);
}

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
		if (!trimmed)
			return (printf("Error\nMalloc failed\n"), 0);
		if (parsed == 6)
		{
			free(trimmed);
			*f_line = line;
			return (1);
		}
		if (!handle_config_line(game, line, trimmed, &parsed))
			return (0);
		line = get_line(fd);
	}
	if (parsed != 6)
		return (printf("Error\nMissing configuration element\n"), 0);
	return (1);
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
		return (printf("Error\nArgument is a derctory!\n"), close(fd), 0);
	f_line = NULL;
	if (!parse_configurations(game, fd, &f_line))
		return (close(fd), 0);
	if (!parse_map(game, fd, f_line))
		return (close(fd), 0);
	close(fd);
	return (1);
}
