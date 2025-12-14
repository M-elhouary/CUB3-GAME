/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:59:34 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/14 02:22:09 by mel-houa         ###   ########.fr       */
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
	int	dx;
	int	dy;
	int	offset_x;
	int	offset_y;

	dy = 0;
	offset_x = game->scren_width - (game->map->width * 5) - 5;
	offset_y = game->scren_height - (game->map->height * 5) - 5;
	while (dy < 5)
	{
		dx = 0;
		while (dx < 5)
		{
			put_pixel(offset_x + x * 5 + dx, offset_y + y * 5 + dy, img,
				0xfbf82b);
			dx++;
		}
		y++;
	}
}

static void	draw_minimap_background(t_img *img)
{
	int	dx;
	int	dy;
	int	offset_x;
	int	offset_y;

	offset_x = game->scren_width - (game->map->width * 5) - 5;
	offset_y = game->scren_height - (game->map->height * 5) - 5;
	dy = 0;
	while (dy < 5)
	{
		dx = 0;
		while (dx < 5)
		{
			put_pixel(offset_x + (x * 5 + dx), offset_y + y * 5 + dy, img,
				0x2b41fb);
			dx++;
		}
		dy++;
	}
}

void	draw_player(t_img *img, t_game *game, double x, double y)
{
	int	dx;
	int	dy;
	int	offset_x;
	int	offset_y;

	offset_x = game->scren_width - (game->map->width * 5) - 5;
	offset_y = game->scren_height - (game->map->height * 5) - 5;
	dy = -4;
	while (dy < 5)
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
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < game->scren_height)
	{
		x = 0;
		while (x < game->scren_width)
		{
			if (y < game->map->height && x < game->map->width
				&& game->map->map_arr[y][x] == '1')
				draw_wall(img, game, x, y);
			else if ((y < game->map->height && x < game->map->width)
				&& (game->map->map_arr[y][x] == '0'
				|| is_player(game->map->map_arr[y][x])))
				draw_floor(img, game, x, y);
			x++;
		}
		map_y++;
	}
	draw_player_icon(game, img, cell_size);
	return (0);
}
