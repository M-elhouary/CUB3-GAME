/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 20:06:42 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/22 22:00:37 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_map_row(int fd)
{
	char	*s;
	int		rows;

	rows = 0;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		free(s);
		rows++;
	}
	close(fd);
	return (rows);
}

char	**allocate_and_read_map(int rows, int fd)
{
	char	*s;
	char	**map;
	int		i;
	
	map = malloc((rows + 1) * sizeof(char *));
	if (!map)
		return (printf("Error\nfrom malloc!\n"), NULL);
	i = 1;
	while ((s = get_next_line(fd)) != NULL && i <= 6)
	{
		free(s);
		i++;
	}
	i = 0;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break;
		map[i++] = s;
		
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int parse_map(t_game *game, int fd,char *filedata)
{
    int i, rows, fd1;
	char *line;
	
	i = 1;
	while ((line = get_next_line(fd)) != NULL && i <= 6)
	{
		free(line);
		i++;
	}
	game->map->height = count_map_row(fd);
	if (game->map->height <= 0)
	{
		free(line);
		return (printf("Error\nMissing the map!\n"), 0);
	}
	fd1 = open(filedata, O_RDONLY);
	game->map->map_arr = allocate_and_read_map(game->map->height, fd1);
	if (!game->map->map_arr)
		return (0);
	printf("the map len : %d\n",ft_strlen_2d(game->map->map_arr));
	return (1);
}