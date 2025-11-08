/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:08:03 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/08 21:01:45 by moirhira         ###   ########.fr       */
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

// double cast_ray(t_game *game, double ray_x, double ray_y)
// {
//     double distance;
//     double max_distance;
//     double step_size;
//     double check_x;
//     double check_y;

//     distance = 0.0;
//     max_distance = 0;
//     step_size = 0.05;
//     while(game->map->map_arr[0][(int)max_distance])
//         max_distance++;
//     while (distance < max_distance)
//     {
//         check_x = game->player.pos_x + ray_x * distance;
//         check_y = game->player.pos_y + ray_y * distance;
//         if (is_wall(game, check_x, check_y) == 1)
//             return (distance);
//         distance += step_size;
//     }
//     return (max_distance);
// }


/**
 * @brief Casts a ray and finds the wall it hits.
 * Still uses your raymarching method, but now returns more information.
 */
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
    return (hit);
}