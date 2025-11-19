/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:08:03 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/19 22:59:00 by mel-houa         ###   ########.fr       */
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

int	check_wall(double check_x, double check_y, t_ray_hit *hit, t_game *game)
{
	if (is_wall(game, check_x, check_y) == 1)
	{
		// We hit a wall! Now, figure out wall_x for texturing.
		if (fabs(check_x - round(check_x)) < 0.01) // Hit a vertical (E/W) wall
		{
			hit->side = 0;
			hit->wall_x = check_y - floor(check_y);
		}
		else // Hit a horizontal (N/S) wall
		{
			hit->side = 1;
			hit->wall_x = check_x - floor(check_x);
		}
		return (1); // Return all the hit info
	}
	return (0);
}
t_ray_hit	cast_ray(t_game *game, double ray_x, double ray_y)
{
	t_ray_hit	hit;
	double		check_x;
	double		check_y;

	hit.distance = 0.0;
	while (hit.distance < 100) // A max distance to prevent infinite loops
	{
		check_x = game->player.pos_x + ray_x * hit.distance;
		check_y = game->player.pos_y + ray_y * hit.distance;
		if (check_wall(check_x, check_y, &hit, game))
			return (hit);
		hit.distance += 0.01; // Take a small step
	}
	hit.distance = 100; // If no wall found, return a large distance
	return (hit);
}
