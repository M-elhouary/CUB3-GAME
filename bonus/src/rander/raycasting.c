/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:08:03 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/14 21:39:41 by moirhira         ###   ########.fr       */
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
            game->player.plane_x = 0.66;
            game->player.plane_y = 0;
    }
    else if (game->player.dir == 'E')    // EAST DIRECTION AND PLANE
    {
        game->player.dir_x = 1;
        game->player.dir_y= 0; 
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (game->player.dir == 'S')  // SOUTH DIRECTION AND PLANE
    {
        game->player.dir_x = 0;
        game->player.dir_y= 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (game->player.dir == 'W')  // WEST DIRECTION AND PLANE
    {
        game->player.dir_x = -1;
        game->player.dir_y= 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }

}

t_ray_hit cast_ray(t_game *game, double ray_x, double ray_y)
{
    t_ray_hit   hit;
    double      check_x;
    double      check_y;

    hit.distance = 0.0;
    while (hit.distance < 100) // A max distance to prevent infinite loops
    {
        check_x = game->player.pos_x + ray_x * hit.distance;
        check_y = game->player.pos_y + ray_y * hit.distance;

        if (is_wall(game, check_x, check_y) == 1)
        {
            // We hit a wall! Now, figure out wall_x for texturing.
            hit.map_x = (int)check_x;
            hit.map_y = (int)check_y;
            if (fabs(check_x - round(check_x)) < 0.01) // Hit a vertical (E/W) wall
            {
                hit.side = 0;
                hit.wall_x = check_y - floor(check_y);
            }
            else // Hit a horizontal (N/S) wall
            {
                hit.side = 1;
                hit.wall_x = check_x - floor(check_x);
            }
            return (hit); // Return all the hit info
        }
        hit.distance += 0.01; // Take a small step
    }
    hit.distance = 100; // If no wall found, return a large distance
    hit.map_x = 0; 
    hit.map_y = 0;
    return (hit);
}