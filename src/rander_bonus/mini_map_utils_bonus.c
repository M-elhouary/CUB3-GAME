/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:16:50 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/21 15:35:57 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	clamp_start(int *sx, int *sy, t_game *g)
{
	int	map_w;
	int	map_h;

	map_h = g->map->height;
	map_w = g->map->width;
	if (map_w <= MINI_MAP_SCALE)
		*sx = 0;
	else
	{
		if (*sx < 0)
			*sx = 0;
		if (*sx + MINI_MAP_SCALE > map_w)
			*sx = map_w - MINI_MAP_SCALE;
	}
	if (map_h <= MINI_MAP_SCALE)
		*sy = 0;
	else
	{
		if (*sy < 0)
			*sy = 0;
		if (*sy + MINI_MAP_SCALE > map_h)
			*sy = map_h - MINI_MAP_SCALE;
	}
}

void	draw_tile_square(t_img *img, int origin_x, int origin_y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			put_pixel(origin_x + dx, origin_y + dy, img, color);
			dx++;
		}
		dy++;
	}
}

void	draw_floor(t_img *img, t_game *game, int x, int y)
{
	(void)game;
	draw_tile_square(img, x * TILE_SIZE, y * TILE_SIZE, FLOOR_COLOR);
}

void	draw_wall(t_img *img, t_game *game, int x, int y)
{
	(void)game;
	draw_tile_square(img, x * TILE_SIZE, y * TILE_SIZE, WALL_COLOR);
}
