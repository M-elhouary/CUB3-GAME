/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@local>                           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:00:00 by auto              #+#    #+#             */
/*   Updated: 2025/12/13 12:00:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	apply_rotation(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

void	open_door(t_game *game)
{
	int		check_x;
	int		check_y;
	char	tile;

	if (game->keys.e == 1)
	{
		printf("opne door\n");
		check_x = (int)(game->player.pos_x + game->player.dir_x * 0.8);
		check_y = (int)(game->player.pos_y + game->player.dir_y * 0.8);
		tile = game->map->map_arr[check_y][check_x];
		if (tile == 'D')
			game->map->map_arr[check_y][check_x] = 'O';
		else if (tile == 'O')
			game->map->map_arr[check_y][check_x] = 'D';
	}
}
