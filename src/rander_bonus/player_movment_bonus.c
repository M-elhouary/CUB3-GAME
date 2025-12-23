/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:07:38 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/21 15:36:01 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	open_door(t_game *game)
{
	int		check_x;
	int		check_y;
	char	tile;

	if (game->keys.e == 1)
	{
		check_x = (int)(game->player.pos_x + game->player.dir_x * 0.8);
		check_y = (int)(game->player.pos_y + game->player.dir_y * 0.8);
		if (check_x < 0 || check_y < 0 || check_y >= game->map->height
			|| check_x >= game->map->width)
			return ;
		tile = game->map->map_arr[check_y][check_x];
		if (tile == 'D')
		{
			game->map->map_arr[check_y][check_x] = 'O';
			game->last_opened_door_x = check_x;
			game->last_opened_door_y = check_y;
			game->door_opened = 1;
		}
		else if (tile == 'O')
		{
			game->map->map_arr[check_y][check_x] = 'D';
			game->door_opened = 0;
		}
	}
}

void	close_door_if_needed(t_game *game)
{
	int	px;
	int	py;

	if (game->door_opened)
	{
		px = (int)game->player.pos_x;
		py = (int)game->player.pos_y;
		if (px != game->last_opened_door_x || py != game->last_opened_door_y)
		{
			if (game->last_opened_door_x >= 0 && game->last_opened_door_y >= 0
				&& game->last_opened_door_y < game->map->height
				&& game->last_opened_door_x < game->map->width)
			{
				if (game->map->map_arr[game->last_opened_door_y]
					[game->last_opened_door_x] == 'O')
					game->map->map_arr[game->last_opened_door_y]
					[game->last_opened_door_x] = 'D';
			}
			game->door_opened = 0;
		}
	}
}

void	move_player(t_game *game)
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;

	move_x = 0.0;
	move_y = 0.0;
	w_s_a_d_movement(game, &move_x, &move_y);
	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	if (is_wall(game, new_x, game->player.pos_y) == 0)
		game->player.pos_x = new_x;
	if (is_wall(game, game->player.pos_x, new_y) == 0)
		game->player.pos_y = new_y;
	close_door_if_needed(game);
}

void	rotate_player(t_game *game, double rot, int f)
{
	double	rot_speed;

	rot_speed = 0;
	if (f == 1)
		rot_speed = rot;
	else
	{
		if (game->keys.right_arrow == 1)
			rot_speed = game->rot_speed;
		else if (game->keys.left_arrow == 1)
			rot_speed = -game->rot_speed;
		else
			return ;
	}
	apply_rotation(game, rot_speed);
}

int	game_update(t_game *game)
{
	move_player(game);
	rotate_player(game, 0, 0);
	open_door(game);
	draw(game, game->img);
	return (0);
}
