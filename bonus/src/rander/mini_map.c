/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:59:34 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/14 23:02:22 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINI_MAP_SCALE 10
#define TILE_SIZE 15

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

static void	draw_tile_square(t_img *img, int origin_x, int origin_y, int color)
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
	draw_tile_square(img, x * TILE_SIZE, y * TILE_SIZE, 0xfbf82b);
}

void	draw_wall(t_img *img, t_game *game, int x, int y)
{
	(void)game;
	draw_tile_square(img, x * TILE_SIZE, y * TILE_SIZE, 0x2b41fb);
}

static void	draw_player_marker(t_img *img, double px, double py)
{
	int	dx;
	int	dy;
	int	screen_x;
	int	screen_y;
	const int	limit = MINI_MAP_SCALE * TILE_SIZE;

	dy = -4;
	while (dy <= 4)
	{
		dx = -4;
		while (dx <= 4)
		{
			screen_x = (int)(px + dx);
			screen_y = (int)(py + dy);
			if (screen_x >= 0 && screen_y >= 0
				&& screen_x < limit && screen_y < limit)
				put_pixel(screen_x, screen_y, img, 0x27F5F2);
			dx++;
		}
		dy++;
	}
}

void	draw_player(t_img *img, t_game *game, double start_x, double start_y)
{
	double	px;
	double	py;

	px = (game->player.pos_x - start_x) * TILE_SIZE;
	py = (game->player.pos_y - start_y) * TILE_SIZE;
	draw_player_marker(img, px, py);
}

int	mini_map(t_game *game, t_img *img)
{
	int	local_y;
	int	local_x;
	int	map_x;
	int	map_y;
	char	tile;
	int	start_x;
	int	start_y;

	start_x = (int)floor(game->player.pos_x) - MINI_MAP_SCALE / 2;
	start_y = (int)floor(game->player.pos_y) - MINI_MAP_SCALE / 2;
	clamp_start(&start_x, &start_y, game);
	local_y = 0;
	while (local_y < MINI_MAP_SCALE)
	{
		map_y = start_y + local_y;
		local_x = 0;
		while (local_x < MINI_MAP_SCALE)
		{
			map_x = start_x + local_x;
			if (map_x >= 0 && map_y >= 0
				&& map_y < game->map->height && map_x < game->map->width)
			{
				tile = game->map->map_arr[map_y][map_x];
				if (tile == '1')
					draw_wall(img, game, local_x, local_y);
				else if (tile == '0' || is_player(tile))
					draw_floor(img, game, local_x, local_y);
				else if (tile == 'D')
					draw_tile_square(img, local_x * TILE_SIZE,
						local_y * TILE_SIZE, 0x8B4513);
			}
			local_x++;
		}
		local_y++;
	}
	draw_player(img, game, start_x, start_y);
	mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
	return (0);
}
