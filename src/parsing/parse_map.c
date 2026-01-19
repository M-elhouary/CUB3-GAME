/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:06:42 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/23 16:24:01 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

char	**append_line(char **map, char *line, int rows)
{
	char	**new_map;
	int		i;

	new_map = ft_malloc((rows + 2) * sizeof(char *));
	i = 0;
	while (i < rows)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i++] = line;
	new_map[i] = NULL;
	return (new_map);
}

int	process_map_line(t_game *game, char *line, int *rows, int *max_width)
{
	strip_newline(line);
	if (ft_strlen(line) > *max_width)
		*max_width = ft_strlen(line);
	game->map->map_arr = append_line(game->map->map_arr, line, *rows);
	if (!game->map->map_arr)
		return (0);
	(*rows)++;
	return (1);
}

int	handle_empty_map_line(int rows)
{
	if (rows > 0)
	{
		printf("Error\nEmpty line inside map definition.\n");
		return (0);
	}
	return (1);
}

int	read_map_lines(t_game *game, int fd, char *first_line)
{
	char	*line;
	int		rows;
	int		max_width;

	rows = 0;
	max_width = 0;
	line = first_line;
	while (line != NULL)
	{
		if (ft_isempty(line))
		{
			if (!handle_empty_map_line(rows))
				return (0);
			line = get_line(fd);
			continue ;
		}
		if (!process_map_line(game, line, &rows, &max_width))
			return (0);
		line = get_line(fd);
	}
	game->map->height = rows;
	game->map->width = max_width;
	if (rows == 0)
		return (printf("Error\nMissing map!\n"), 0);
	return (1);
}
