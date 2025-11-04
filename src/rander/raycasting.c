/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:08:03 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/04 23:09:40 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



// Set initial direction and camera plane based on player starting orientation
void camera(t_game *game)
{

// NORTH DIRECTION AND PLANE
    if (game->player.dir == 'N')  // NORTH DIRECTION AND PLANE
    {
            game->player.dir_x = 0;
            game->player.dir_y = -1;
            game->player.plan_x = 0.66;
            game->player.plan_y = 0;
    }
    else if (game->player.dir == 'E')    // EAST DIRECTION AND PLANE
    {
        game->player.dir_x = 1;
        game->player.dir_y= 0; 
        game->player.plan_x = 0;
        game->player.plan_y = 0.66;
    }
    else if (game->player.dir == 'S')  // SOUTH DIRECTION AND PLANE
    {
        game->player.dir_x = 0;
        game->player.dir_y= 1;
        game->player.plan_x = -0.66;
        game->player.plan_y = 0;
    }
    else if (game->player.dir == 'W')  // WEST DIRECTION AND PLANE
    {
        game->player.dir_x = -1;
        game->player.dir_y= 0;
        game->player.plan_x = 0;
        game->player.plan_y = -0.66;
    }

}

double cast_ray(t_game *game, double ray_x, double ray_y)
{
    double distance;
    double max_distance;
    double step_size;
    double check_x;
    double check_y;

    distance = 0.0;
    max_distance = 0;
    step_size = 0.05;
    while(game->map->map_arr[0][(int)max_distance])
        max_distance++;
    while (distance < max_distance)
    {
        check_x = game->player.x + ray_x * distance;
        check_y = game->player.y + ray_y * distance;
        if (is_wall(game, check_x, check_y) == 1)
            return (distance);
        distance += step_size;
    }
    return (max_distance);
}
