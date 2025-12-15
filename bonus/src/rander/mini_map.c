/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:59:34 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/15 02:29:05 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_mm_ctx
{
	t_game	*game;
	t_img	*img;
	int		start_x;
	int		start_y;
}	t_mm_ctx;

static void	draw_player_marker(t_img *img, double px, double py)
{
	int	dx;
	int	dy;
	int	screen_x;
	int	screen_y;
	int	limit;

	limit = MINI_MAP_SCALE * TILE_SIZE;
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
				put_pixel(screen_x, screen_y, img, PLAYER_COLOR);
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

static void	render_tile_ctx(t_mm_ctx *ctx, int local_x, int local_y)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = ctx->start_x + local_x;
	map_y = ctx->start_y + local_y;
	if (map_x < 0 || map_y < 0
		|| map_y >= ctx->game->map->height
		|| map_x >= ctx->game->map->width)
		return ;
	tile = ctx->game->map->map_arr[map_y][map_x];
	if (tile == '1')
		draw_wall(ctx->img, ctx->game, local_x, local_y);
	else if (tile == '0' || is_player(tile))
		draw_floor(ctx->img, ctx->game, local_x, local_y);
	else if (tile == 'D')
		draw_tile_square(ctx->img, local_x * TILE_SIZE,
			local_y * TILE_SIZE, DOOR_COLOR);
}

int	mini_map(t_game *game, t_img *img)
{
	int			local_y;
	int			local_x;
	t_mm_ctx	ctx;

	ctx.game = game;
	ctx.img = img;
	ctx.start_x = (int)floor(game->player.pos_x) - MINI_MAP_SCALE / 2;
	ctx.start_y = (int)floor(game->player.pos_y) - MINI_MAP_SCALE / 2;
	clamp_start(&ctx.start_x, &ctx.start_y, game);
	local_y = 0;
	while (local_y < MINI_MAP_SCALE)
	{
		local_x = 0;
		while (local_x < MINI_MAP_SCALE)
		{
			render_tile_ctx(&ctx, local_x, local_y);
			local_x++;
		}
		local_y++;
	}
	draw_player(img, game, ctx.start_x, ctx.start_y);
	mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
	return (0);
}
