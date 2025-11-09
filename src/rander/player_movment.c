/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:07:38 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/09 12:56:28 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int is_wall(t_game *game, double x, double y)
{

    int new_x;
    int new_y;
    new_x = (int)(x);
    new_y = (int)(y);
    if(new_x < 0 || new_y < 0 || new_y >= game->map->height || game->map->width <= new_x)
        return 1; 
    if(game->map->map_arr[new_y][new_x] == '1')
        return 1;
    return 0;
}


void move_player(t_game *game)
{
	double move_x;
	double move_y;
	double new_x;
	double new_y;

	move_x = 0.0;
	move_y = 0.0;
	if (game->keys.w == 1)
	{
		move_x += game->player.dir_x * game->move_speed;
		move_y += game->player.dir_y * game->move_speed;
	}
	if (game->keys.s == 1)
	{
		move_x -= game->player.dir_x * game->move_speed;
		move_y -= game->player.dir_y * game->move_speed;
	}
	if (game->keys.a == 1)
	{
		move_x -= game->player.plane_x * game->move_speed;
		move_y -= game->player.plane_y * game->move_speed;
	}
	if (game->keys.d == 1)
	{
		move_x += game->player.plane_x * game->move_speed;
		move_y += game->player.plane_y * game->move_speed;
	}
	// printf("Pos: (%.2f, %.2f) | Dir: (%.2f, %.2f)\n", 
    //         game->player.pos_x, game->player.pos_y, 
    //         game->player.dir_x, game->player.dir_y);
	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	
	if (is_wall(game, new_x, game->player.pos_y) == 0)
		game->player.pos_x = new_x;
		
	if (is_wall(game, game->player.pos_x, new_y) == 0)
		game->player.pos_y = new_y;
		
}

void rotate_player(t_game *game)
{
	double rot_speed;
	double old_dir_x;
	double old_plane_x;
	
	if (game->keys.right_arrow == 1)
	{
		printf("right arrow\n");
		rot_speed = game->rot_speed;
	}
	else if (game->keys.left_arrow == 1)
	{
		rot_speed = -game->rot_speed;
		printf("left arrow\n");
	}
	else
		return ;
		
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
		
	
}

int game_update(t_game *game)
{
	move_player(game);
	rotate_player(game);
	draw(game, game->img);
	return (0);
}