/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:01:32 by moirhira          #+#    #+#             */
/*   Updated: 2025/09/23 12:35:30 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	only_valid_chars(t_game *game)
{
	char	c;
	int		i;
	int		j;
    
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (game->map->map_arr[i][j])
		{
			c = game->map->map_arr[i][j];
			if (!(c == '0' || c == '1' || c == ' ' || is_player(c)))
				return (printf("Error\nInvalid character '%c' in map!\n", c),0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_player_count(t_game *game)
{
	int		x;
	int		y;
    int player_count;
    
	x = -1;
    player_count = 0;
	while (++x < game->map->height)
	{
		y = -1;
		while (game->map->map_arr[x][++y])
		{
            if (is_player(game->map->map_arr[x][y]))
			{
                player_count++;
				game->player.x = x;
				game->player.y = y;
				game->player.dir = game->map->map_arr[x][y];
			}
		}
	}
    if (player_count == 0)
		return (printf("Error\nNo player found!\n"), 0);
	if (player_count != 1)
		return (printf("Error\nDuplicate player!\n"), 0);
    return (1);
}

int	are_neighbors_valid(t_game *game, int y, int x)
{
	char **map;

	map = game->map->map_arr;
	if (y == 0  || ft_strlen(map[y - 1]) <= x || map[y - 1][x] == ' ')
		return (0);
	if (y == game->map->height - 1 || ft_strlen(map[y + 1]) <= x || map[y + 1][x] == ' ')
		return (0);
	if (x == 0 || map[y][x - 1] == ' ')
		return (0);
	if (map[y][x + 1] == '\0' || map[y][x + 1] == ' ')
		return (0);	
	return (1);
}

int	check_walls(t_game *game)
{
	int	x;
	int	y;
    char c;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->map_arr[y][x])
		{
            c = game->map->map_arr[y][x];
			if (c == '0' || is_player(c))
			{
				if (!are_neighbors_valid(game, y, x))
					return (printf("Error\nMap is not closed! Gap at (%d, %d)\n", y, x), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}



int	validate_map(t_game *game)
{
	int	i;
    int player_count;

	i = 0;
    player_count = 0;
	if (!only_valid_chars(game))
		return (0);
    if (!check_player_count(game))
        return (0);
    if (!check_walls(game))
		return (0);
	return (1);
}