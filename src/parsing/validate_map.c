/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:01:32 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/10 16:46:14 by moirhira         ###   ########.fr       */
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
				return (printf("Error\nInvalid character '%c' in map!\n", c),
					0);
			j++;
		}
		i++;
	}
	return (1);
}

void	set_player_data(t_game *game, int x, int y, char c)
{
	game->player.pos_x = x;
	game->player.pos_y = y;
	game->player.dir = c;
	game->map->map_arr[y][x] = '0';
}

int	check_player_count(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	y = -1;
	player_count = 0;
	while (++y < game->map->height)
	{
		x = -1;
		while (game->map->map_arr[y][++x])
		{
			if (is_player(game->map->map_arr[y][x]))
			{
				player_count++;
				set_player_data(game, x, y, game->map->map_arr[y][x]);
			}
		}
	}
	if (player_count == 0)
		return (printf("Error\nNo player found!\n"), 0);
	if (player_count != 1)
		return (printf("Error\nDuplicate player!\n"), 0);
	return (1);
}

int	validate_map(t_game *game)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	if (!only_valid_chars(game))
		return (0);
	if (!check_player_count(game))
		return (0);
	if (!check_map_is_closed(game))
		return (0);
	return (1);
}
