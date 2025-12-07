/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:08:03 by mel-houa          #+#    #+#             */
/*   Updated: 2025/11/26 01:10:18 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit_wall;
	int		side;
}			t_dda;

static void	calc_side_x(t_game *game, t_dda *dda, double ray_x)
{
	if (ray_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player.pos_x - dda->map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - game->player.pos_x)
			* dda->delta_dist_x;
	}
}

static void	calc_side_y(t_game *game, t_dda *dda, double ray_y)
{
	if (ray_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player.pos_y - dda->map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - game->player.pos_y)
			* dda->delta_dist_y;
	}
}

void	calcule_side(t_game *game, t_dda *dda, double ray_x, double ray_y)
{
	dda->map_x = (int)game->player.pos_x;
	dda->map_y = (int)game->player.pos_y;
	dda->delta_dist_x = fabs(1 / ray_x);
	dda->delta_dist_y = fabs(1 / ray_y);
	calc_side_x(game, dda, ray_x);
	calc_side_y(game, dda, ray_y);
}

void	calc_perp_dist(t_dda *dda, t_game *game)
{
	while (dda->hit_wall == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_y < 0 || dda->map_y >= game->map->height || dda->map_x < 0
			|| dda->map_x >= game->map->width)
			dda->hit_wall = 1;
		else if (game->map->map_arr[dda->map_y][dda->map_x] == '1')
			dda->hit_wall = 1;
	}
}

t_ray_hit	cast_ray(t_game *game, double ray_x, double ray_y)
{
	t_ray_hit	hit;
	t_dda		dda;

	dda.hit_wall = 0;
	calcule_side(game, &dda, ray_x, ray_y);
	calc_perp_dist(&dda, game);
	if (dda.side == 0)
		dda.perp_wall_dist = (dda.side_dist_x - dda.delta_dist_x);
	else
		dda.perp_wall_dist = (dda.side_dist_y - dda.delta_dist_y);
	hit.distance = dda.perp_wall_dist;
	hit.side = dda.side;
	if (dda.side == 0)
		hit.wall_x = game->player.pos_y + dda.perp_wall_dist * ray_y;
	else
		hit.wall_x = game->player.pos_x + dda.perp_wall_dist * ray_x;
	hit.wall_x -= floor(hit.wall_x);
	hit.map_x = dda.map_x;
	hit.map_y = dda.map_y;
	return (hit);
}
