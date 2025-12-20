/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 02:22:52 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/15 01:57:35 by mel-houa         ###   ########.fr       */
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

int	is_wall(t_game *game, double x, double y)
{
	int	new_x;
	int	new_y;

	new_x = (int)(x);
	new_y = (int)(y);
	if (new_x < 0 || new_y < 0 || new_y >= game->map->height
		|| game->map->width <= new_x)
		return (1);
	if (game->map->map_arr[new_y][new_x] == '1'
		|| game->map->map_arr[new_y][new_x] == 'D')
		return (1);
	return (0);
}

void	w_s_a_d_movement(t_game *game, double *move_x, double *move_y)
{
	if (game->keys.w == 1)
	{
		*move_x += game->player.dir_x * game->move_speed;
		*move_y += game->player.dir_y * game->move_speed;
	}
	if (game->keys.s == 1)
	{
		*move_x -= game->player.dir_x * game->move_speed;
		*move_y -= game->player.dir_y * game->move_speed;
	}
	if (game->keys.a == 1)
	{
		*move_x -= game->player.plane_x * game->move_speed;
		*move_y -= game->player.plane_y * game->move_speed;
	}
	if (game->keys.d == 1)
	{
		*move_x += game->player.plane_x * game->move_speed;
		*move_y += game->player.plane_y * game->move_speed;
	}
}
