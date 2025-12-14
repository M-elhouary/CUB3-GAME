/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:59:34 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/13 23:28:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_SIZE 150
#define MINIMAP_OFFSET_X 20
#define MINIMAP_OFFSET_Y 20
#define MINIMAP_RANGE 6
#define MINIMAP_BG_COLOR 0x220f0f
#define MINIMAP_BORDER_COLOR 0xfefefe
#define MINIMAP_WALL_COLOR 0x2b41fb
#define MINIMAP_FLOOR_COLOR 0x3a3a3a
#define MINIMAP_PLAYER_COLOR 0x27f5f2

static void	draw_rect_clipped(t_img *img, int left, int top, int size, int color)
{
	int		x;
	int		y;
	int		max_x;
	int		max_y;

	max_x = MINIMAP_OFFSET_X + MINIMAP_SIZE;
	max_y = MINIMAP_OFFSET_Y + MINIMAP_SIZE;
	if (left >= max_x || top >= max_y || left + size <= MINIMAP_OFFSET_X
		|| top + size <= MINIMAP_OFFSET_Y)
		return;
	y = 0;
	while (y < size)
	{
		int screen_y = top + y;
		if (screen_y < MINIMAP_OFFSET_Y || screen_y >= max_y)
		{
			y++;
			continue;
		}
		x = 0;
		while (x < size)
		{
			int screen_x = left + x;
			if (screen_x >= MINIMAP_OFFSET_X && screen_x < max_x)
				put_pixel(screen_x, screen_y, img, color);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_background(t_img *img)
{
	int	y;
	int	x;

	y = MINIMAP_OFFSET_Y;
	while (y < MINIMAP_OFFSET_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_OFFSET_X;
		while (x < MINIMAP_OFFSET_X + MINIMAP_SIZE)
		{
			put_pixel(x, y, img, MINIMAP_BG_COLOR);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		put_pixel(MINIMAP_OFFSET_X + y, MINIMAP_OFFSET_Y, img,
			MINIMAP_BORDER_COLOR);
		put_pixel(MINIMAP_OFFSET_X + y, MINIMAP_OFFSET_Y + MINIMAP_SIZE - 1,
			img, MINIMAP_BORDER_COLOR);
		put_pixel(MINIMAP_OFFSET_X, MINIMAP_OFFSET_Y + y, img,
			MINIMAP_BORDER_COLOR);
		put_pixel(MINIMAP_OFFSET_X + MINIMAP_SIZE - 1, MINIMAP_OFFSET_Y + y,
			img, MINIMAP_BORDER_COLOR);
		y++;
	}
}

static void	draw_tile(t_img *img, double local_x, double local_y, double cell_size,
			int color)
{
	double	center_x;
	double	center_y;
	int		size_px;
	int		left;
	int		top;

	center_x = MINIMAP_OFFSET_X + (MINIMAP_SIZE / 2.0)
		+ local_x * cell_size;
	center_y = MINIMAP_OFFSET_Y + (MINIMAP_SIZE / 2.0)
		+ local_y * cell_size;
	size_px = (int)(cell_size);
	if (size_px < 2)
		size_px = 2;
	left = (int)(center_x - (size_px / 2.0));
	top = (int)(center_y - (size_px / 2.0));
	draw_rect_clipped(img, left, top, size_px, color);
}

static void	draw_player_icon(t_game *game, t_img *img, double cell_size)
{
	int		radius;
	int		px;
	int		py;
	int		x;
	int		y;
	int		line_len;
	int		end_x;
	int		end_y;

	px = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
	py = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
	radius = (int)(cell_size / 3.0);
	if (radius < 2)
		radius = 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(px + x, py + y, img, MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
	line_len = (int)(cell_size * 1.5);
	end_x = px + (int)(game->player.dir_x * line_len);
	end_y = py + (int)(game->player.dir_y * line_len);
	y = 0;
	while (y <= line_len)
	{
		int draw_x = px + (int)(game->player.dir_x * y);
		int draw_y = py + (int)(game->player.dir_y * y);
		if (draw_x >= MINIMAP_OFFSET_X && draw_x < MINIMAP_OFFSET_X + MINIMAP_SIZE
			&& draw_y >= MINIMAP_OFFSET_Y && draw_y < MINIMAP_OFFSET_Y
				+ MINIMAP_SIZE)
			put_pixel(draw_x, draw_y, img, MINIMAP_PLAYER_COLOR);
		y++;
	}
}

int	mini_map(t_game *game, t_img *img)
{
	int		map_y;
	int		map_x;
	double		cell_size;
	double		local_x;
	double		local_y;
	int		max_y;
	int		max_x;

	draw_minimap_background(img);
	cell_size = (double)MINIMAP_SIZE / (double)((MINIMAP_RANGE * 2) + 1);
	map_y = (int)floor(game->player.pos_y) - MINIMAP_RANGE;
	max_y = (int)floor(game->player.pos_y) + MINIMAP_RANGE;
	while (map_y <= max_y)
	{
		map_x = (int)floor(game->player.pos_x) - MINIMAP_RANGE;
		max_x = (int)floor(game->player.pos_x) + MINIMAP_RANGE;
		while (map_x <= max_x)
		{
			if (map_y >= 0 && map_y < game->map->height && map_x >= 0
				&& map_x < game->map->width)
			{
				local_x = (map_x + 0.5) - game->player.pos_x;
				local_y = (map_y + 0.5) - game->player.pos_y;
				if (game->map->map_arr[map_y][map_x] == '1')
					draw_tile(img, local_x, local_y, cell_size, MINIMAP_WALL_COLOR);
				else if (game->map->map_arr[map_y][map_x] == '0'
					|| check_player(game->map->map_arr[map_y][map_x])
					|| game->map->map_arr[map_y][map_x] == 'D')
					draw_tile(img, local_x, local_y, cell_size,
						MINIMAP_FLOOR_COLOR);
			}
			map_x++;
		}
		map_y++;
	}
	draw_player_icon(game, img, cell_size);
	return (0);
}
