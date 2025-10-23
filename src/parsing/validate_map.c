/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:01:32 by moirhira          #+#    #+#             */
/*   Updated: 2025/10/23 22:35:40 by moirhira         ###   ########.fr       */
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
			}
		}
	}
    if (player_count == 0)
		return (printf("Error\nNo player found!\n"), 0);
	if (player_count != 1)
		return (printf("Error\nDuplicate player!\n"), 0);
    return (1);
}

char **fill_map_with_spaces(t_game *game)
{
	int i;
	int line_len;
	char **new_map;
	
	new_map = malloc(sizeof(char*) * game->map->height + 1);
	if (!new_map)
		return (printf("Error\nMalloc failed\n"), NULL);
	i = 0;
	while (i < game->map->height)
	{
		new_map[i] = malloc((game->map->width + 1) * sizeof(char));
		if (!new_map[i])
		{
			free_split(new_map);
			return (printf("Error\nMalloc failed\n"), NULL);
		}
		line_len = ft_strlen(game->map->map_arr[i]);
		ft_memcpy(new_map[i], game->map->map_arr[i], line_len);
		ft_memset(new_map[i] + line_len, ' ', game->map->width - line_len);
		new_map[i][game->map->width] = '\0';
		i++;
	}
	new_map[i]= NULL;
	return (new_map);
}

int	check_map_is_closed(t_game *game)
{
	int	i;
	int	j;
    char c;
    int line_len;
	char **map;

	i = 0;
	map = fill_map_with_spaces(game);
	
	while (i < game->map->height)
	{
		j = 0;
        line_len = ft_strlen(map[i]);
		while (map[i][j])
		{
            c = map[i][j];
			if (i == 0 || i == game->map->height - 1 || j == 0 || j == line_len - 1)
			{
				if (c != '1' && c != ' ')
					return (printf("Error\nMap is not enclosed by walls! at (%d, %d)\n", i , j), 0);
			}
			if (c == '0' || is_player(c))
			{
				if (map[i - 1][j] == ' ')
				{
					return(printf("Error\nMap leaked\n"), 0);
				}
				if (map[i + 1][j] == ' ')
				{
					return(printf("Error\nMap leaked\n"), 0);
				}
				if (map[i][j + 1] == ' ')
				{
					return(printf("Error\nMap leaked\n"), 0);
				}
				if (map[i][j - 1 ] == ' ')
				{
					return(printf("Error\nMap leaked\n"), 0);
				}
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
	if(!check_map_is_closed(game))
		return (0);
	return (1);
}