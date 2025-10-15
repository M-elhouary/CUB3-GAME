/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:06:42 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 10:57:19 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void strip_newline(char *line)
{
	int len;

    if (!line)
        return;
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
	
	new_map = malloc((rows + 2) * sizeof(char *));
	if (!new_map)
		return (printf("Error\nFrom malloc!\n"), NULL);
	i = 0;
	while (i < rows)
	{
		new_map[i] = map[i];
		i++;	
	}
	new_map[i++] = line;
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

int parse_map(t_game *game, int fd, char *first_line)
{
    int max_width;
	int rows;
	int map_started;
	char *line;
	char **map = NULL;
	
	max_width = 0;
	rows = 0;
	map_started = 0;
	line = first_line;
	while (line  != NULL)
	{
		if (ft_isempty(line))
		{
			if (map_started)
			{
				free(line);
                free_split(map);
                return (printf("Error\nEmpty line inside map definition.\n"), 0);
			}
			free(line);
			line = get_next_line(fd);
			continue;
		}
		map_started = 1;
		strip_newline(line);
		if (ft_strlen(line) > max_width)
			max_width = ft_strlen(line);
		map = append_line(map, line, rows);
		if (!map)
			return (free(line), 0);
		rows++;
		line = get_next_line(fd);
	}
	if (rows == 0)
		return( printf("Error\nMissing map!\n"), 0);
	game->map->map_arr = map;
	game->map->height = rows;
	game->map->width = max_width;
	// printf("rows	-> %d\n", game->map->height);
	// printf("cols	-> %d\n", game->map->width);
	// printf("len 	-> %d\n", ft_strlen_2d(game->map->map_arr));
	if (!validate_map(game))
		return (0);
	return (1);
}

