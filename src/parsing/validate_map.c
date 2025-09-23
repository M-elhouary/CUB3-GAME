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
		while (j < (line_len - 1))
		{
			c = game->map->map_arr[i][j];
			if (!(c == '0' || c == '1' || c == ' ' || c == 'N'
                    || c == 'S' || c == 'E' || c == 'W'))
				return (printf("Error\nInvalid character '%c' in map!\n", c),0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_player_count(t_game *game)
{
    char	c;
	int		i;
	int		j;
    int player_count;
    
	i = 0;
    player_count = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (game->map->map_arr[i][j])
		{
			c = game->map->map_arr[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
			j++;
		}
		i++;
	}
    if (player_count == 0)
		return (printf("Error\nNo player found!\n"), 0);
	if (player_count != 1)
		return (printf("Error\nDuplicate player!\n"), 0);
    return (1);
}

int	chek_walls(t_game *game)
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
		while (k < line_len - 1)
		{
            c = game->map->map_arr[i][k];
			if (i == 0 || i == game->map->height - 1 || k == 0 || k == line_len - 2)
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
    if (!chek_walls(game))
		return (0);
	return (1);
}