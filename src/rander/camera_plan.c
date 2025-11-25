/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:43:13 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/25 15:46:13 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



void	north_east(t_game *game)
{
	if (game->player.dir == 'N') // NORTH DIRECTION AND PLANE
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->player.dir == 'E') // EAST DIRECTION AND PLANE
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
}

void	south_west(t_game *game)
{
	if (game->player.dir == 'S') // SOUTH DIRECTION AND PLANE
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->player.dir == 'W') // WEST DIRECTION AND PLANE
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

// Set initial direction and camera plane based on player starting orientation
void	camera(t_game *game)
{
	north_east(game);
	south_west(game);
}