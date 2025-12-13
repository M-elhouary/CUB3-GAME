/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:59:34 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/11 18:53:31 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_floor(t_img *img, t_game *game, int x, int y)
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
		dy++;
	}
}

void	draw_wall(t_img *img, t_game *game, int x, int y)
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
		dx = -4;
		while (dx < 5)
		{
			put_pixel((offset_x + (int)(x * 5) + (dx)), (offset_y + (int)(y * 5)
					+ (dy)), img, 0x27F5F2);
			dx++;
		}
		dy++;
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
			else if (y < game->map->height && x < game->map->width
				&& (game->map->map_arr[y][x] == '0'
				|| is_player(game->map->map_arr[y][x])))
				draw_floor(img, game, x, y);
			x++;
		}
		y++;
	}
	draw_player(img, game, game->player.pos_x, game->player.pos_y);
	mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
	return (0);
}
