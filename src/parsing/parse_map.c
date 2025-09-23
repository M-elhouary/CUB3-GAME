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

int parse_map(t_game *game, int fd)
{
    int max_width, rows;
	char *line;
	char **map = NULL;
	
	max_width = 0;
	rows = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_isempty(line))
		{
			free(line);
			continue;
		}
		if (ft_strlen(line) > max_width)
			max_width = ft_strlen(line);
		map = append_line(map, line, rows);
		if (!map)
			return (printf("Error\nFrom malloc!\n"), 0);
		rows++;
	}
	if (rows == 0)
		return( printf("Error\nMissing map!\n"), 0);
	game->map->map_arr = map;
	game->map->height = rows;
	game->map->width = max_width;
	if (!validate_map(game))
		return (0);
	return (1);
}

