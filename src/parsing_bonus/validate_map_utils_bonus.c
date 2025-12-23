/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:56:23 by moirhira          #+#    #+#             */
/*   Updated: 2025/12/21 19:42:49 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	**fill_map_with_spaces(t_game *game)
{
	int		i;
	int		line_len;
	char	**new_map;

	new_map = ft_malloc(sizeof(char *) * (game->map->height + 1));
	if (!new_map)
		return (printf("Error\nMalloc failed\n"), NULL);
	i = 0;
	while (i < game->map->height)
	{
		new_map[i] = ft_malloc((game->map->width + 1) * sizeof(char));
		if (!new_map[i])
		{
			return (printf("Error\nMalloc failed\n"), NULL);
		}
		line_len = ft_strlen(game->map->map_arr[i]);
		ft_memcpy(new_map[i], game->map->map_arr[i], line_len);
		ft_memset(new_map[i] + line_len, ' ', game->map->width - line_len);
		new_map[i][game->map->width] = '\0';
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	validate_border_and_interior(char **map, t_game *game, int i, int j)
{
	char	c;
	int		line_len;

	c = map[i][j];
	line_len = ft_strlen(map[i]);
	if (i == 0 || i == game->map->height - 1 || j == 0 || j == line_len - 1)
	{
		if (c != '1' && c != ' ')
		{
			printf("Error\nMap is not enclosed by walls! at (%d,%d)\n", i, j);
			return (0);
		}
	}
	if (c == '0' || is_player(c))
	{
		if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j + 1] == ' '
			|| map[i][j - 1] == ' ')
			return (printf("Error\nMap leaked\n"), 0);
	}
	return (1);
}

int	check_map_is_closed(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = fill_map_with_spaces(game);
	if (!map)
		return (0);
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (map[i][j])
		{
			if (!validate_border_and_interior(map, game, i, j))
				return (0);
			j++;
		}
		i++;
	}
	game->map->map_arr = map;
	return (1);
}
