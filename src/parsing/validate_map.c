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
    int line_len;
    
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
        line_len = ft_strlen(game->map->map_arr[i]);
		while (j < line_len)
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

int	check_walls(t_game *game)
{
	int	i;
	int	k;
    char c;
    int line_len;

	i = 0;
	while (i < game->map->height)
	{
		k = 0;
        line_len = ft_strlen(game->map->map_arr[i]);
		while (k < line_len)
		{
            c = game->map->map_arr[i][k];
			if (i == 0 || i == game->map->height - 1 || k == 0 || k == line_len - 1)
			{
				if (c != '1' && c != ' ')
					return (printf("Error\nMap is not enclosed by walls!\n"), 0);
			}
			k++;
		}
		i++;
	}
	return (1);
}

int	check_spaces(t_game *game)
{
	int	i;
	int	j;
	char **map;
    int line_len;

	i = 0;
	map = game->map->map_arr;
	while (i < game->map->height)
	{
		j = 0;
        line_len = ft_strlen(game->map->map_arr[i]);
		while (j < line_len)
		{
			if (map[i][j] == ' ')
			{
				if (i > 0 && (map[i - 1][j] == '0' || is_player(map[i - 1][j])))
					return (printf("Error\nSpace next to floor/player!\n"), 0);
				if (i < game->map->height - 1 && (map[i + 1][j] == '0' || is_player(map[i + 1][j])))
					return (printf("Error\nSpace next to floor/player!\n"), 0);
				if (j > 0 && (map[i][j - 1] == '0' || is_player(map[i][j - 1])))
					return (printf("Error\nSpace next to floor/player!\n"), 0);
				if (map[i][j + 1] && (map[i][j + 1] == '0' || is_player(map[i][j + 1])))
					return (printf("Error\nSpace next to floor/player!\n"), 0);	
			}			
			j++;
		}
		i++;
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
	if (!check_spaces(game))
		return (0);
	return (1);
}