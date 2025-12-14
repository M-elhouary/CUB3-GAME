/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:43:13 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/13 23:06:52 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	north_east(t_game *game)
{
	if (game->player.dir == 'N')
	{
		game->player.dir_x = 0.001;
		game->player.dir_y = -1.001;
		game->player.plane_x = 0.6601;
		game->player.plane_y = 0.001;
	}
	else if (game->player.dir == 'E')
	{
		game->player.dir_x = 1.001;
		game->player.dir_y = 0.001;
		game->player.plane_x = 0.001;
		game->player.plane_y = 0.6601;
	}
}

void	south_west(t_game *game)
{
	if (game->player.dir == 'S')
	{
		game->player.dir_x = 0.001;
		game->player.dir_y = 1.001;
		game->player.plane_x = -0.6601;
		game->player.plane_y = 0.001;
	}
	else if (game->player.dir == 'W')
	{
		game->player.dir_x = -1.001;
		game->player.dir_y = 0.001;
		game->player.plane_x = 0.001;
		game->player.plane_y = -0.6601;
	}
}

void	camera(t_game *game)
{
	north_east(game);
	south_west(game);
}