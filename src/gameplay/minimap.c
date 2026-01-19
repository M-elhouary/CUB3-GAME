/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MINIMAP_SIZE 150
#define MINIMAP_SCALE 2

/*
** Draw a single pixel safely with bounds checking
*/
static void	minimap_put_pixel(t_img *img, int x, int y, int color)
{
	int	pixel_index;

	if (!img || !img->img_pex_ptr)
		return ;
	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	pixel_index = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
	if (pixel_index < 0)
		return ;
	*(unsigned int *)(img->img_pex_ptr + pixel_index) = color;
}

/*
** Draw a filled rectangle on minimap
*/
static void	minimap_draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			minimap_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/*
** Draw minimap background and border
*/
static void	draw_minimap_background(t_game *game, t_img *img)
{
	int	start_x;
	int	start_y;
	int	i;

	if (!game || !img)
		return ;
	start_x = game->scren_width - MINIMAP_SIZE - 10;
	start_y = game->scren_height - MINIMAP_SIZE - 10;
	
	/* Dark background */
	minimap_draw_rect(img, start_x, start_y, MINIMAP_SIZE, MINIMAP_SIZE, 0x1a1a1a);
	
	/* Border */
	i = 0;
	while (i <= MINIMAP_SIZE)
	{
		minimap_put_pixel(img, start_x + i, start_y, 0x00FF00);
		minimap_put_pixel(img, start_x + i, start_y + MINIMAP_SIZE, 0x00FF00);
		minimap_put_pixel(img, start_x, start_y + i, 0x00FF00);
		minimap_put_pixel(img, start_x + MINIMAP_SIZE, start_y + i, 0x00FF00);
		i++;
	}
}

/*
** Draw walls on minimap
** Shows map layout in 2D top-down view
*/
static void	draw_minimap_walls(t_game *game, t_img *img)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	start_x;
	int	start_y;

	if (!game || !game->map || !img)
		return ;
	start_x = game->scren_width - MINIMAP_SIZE - 10;
	start_y = game->scren_height - MINIMAP_SIZE - 10;
	
	map_y = 0;
	while (map_y < game->map->height && map_y < MINIMAP_SIZE / MINIMAP_SCALE)
	{
		map_x = 0;
		while (map_x < game->map->width && map_x < MINIMAP_SIZE / MINIMAP_SCALE)
		{
			if (game->map->map_arr[map_y][map_x] == '1')
			{
				pixel_x = start_x + (map_x * MINIMAP_SCALE);
				pixel_y = start_y + (map_y * MINIMAP_SCALE);
				minimap_draw_rect(img, pixel_x, pixel_y, MINIMAP_SCALE, 
					MINIMAP_SCALE, 0x808080);
			}
			map_x++;
		}
		map_y++;
	}
}

/*
** Draw player position on minimap (blue dot)
*/
static void	draw_minimap_player(t_game *game, t_img *img)
{
	int	pixel_x;
	int	pixel_y;
	int	start_x;
	int	start_y;
	int	max_visible;

	if (!game || !img || !game->map)
		return ;
	start_x = game->scren_width - MINIMAP_SIZE - 10;
	start_y = game->scren_height - MINIMAP_SIZE - 10;
	max_visible = MINIMAP_SIZE / MINIMAP_SCALE;
	
	pixel_x = start_x + ((int)game->player.pos_x * MINIMAP_SCALE);
	pixel_y = start_y + ((int)game->player.pos_y * MINIMAP_SCALE);
	
	/* Only draw if player is within visible minimap bounds */
	if (game->player.pos_x >= 0 && game->player.pos_x < max_visible &&
		game->player.pos_y >= 0 && game->player.pos_y < max_visible)
	{
		/* Draw player as 3x3 blue square */
		minimap_draw_rect(img, pixel_x - 1, pixel_y - 1, 3, 3, 0x0000FF);
	}
}

/*
** Draw enemies on minimap (red dots)
*/
static void	draw_minimap_enemies(t_game *game, t_img *img)
{
	t_object	*current;
	int			pixel_x;
	int			pixel_y;
	int			start_x;
	int			start_y;
	int			max_visible;

	if (!game || !img || !game->objects || !game->map)
		return ;
	start_x = game->scren_width - MINIMAP_SIZE - 10;
	start_y = game->scren_height - MINIMAP_SIZE - 10;
	max_visible = MINIMAP_SIZE / MINIMAP_SCALE;
	
	current = game->objects;
	while (current)
	{
		if (current->type == OBJ_ENEMY && current->visible && current->health > 0)
		{
			/* Only draw if within visible minimap bounds */
			if (current->pos_x >= 0 && current->pos_x < max_visible &&
				current->pos_y >= 0 && current->pos_y < max_visible)
			{
				pixel_x = start_x + ((int)current->pos_x * MINIMAP_SCALE);
				pixel_y = start_y + ((int)current->pos_y * MINIMAP_SCALE);
				
				/* Draw enemy as 2x2 red square */
				minimap_draw_rect(img, pixel_x - 1, pixel_y - 1, 2, 2, 0xFF0000);
			}
		}
		current = current->next;
	}
}

/*
** Draw objects on minimap (yellow dots for items, green for doors)
*/
static void	draw_minimap_objects(t_game *game, t_img *img)
{
	t_object	*current;
	int			pixel_x;
	int			pixel_y;
	int			start_x;
	int			start_y;
	int			color;
	int			max_visible;

	if (!game || !img || !game->objects || !game->map)
		return ;
	start_x = game->scren_width - MINIMAP_SIZE - 10;
	start_y = game->scren_height - MINIMAP_SIZE - 10;
	max_visible = MINIMAP_SIZE / MINIMAP_SCALE;
	
	current = game->objects;
	while (current)
	{
		if (current->visible && current->type != OBJ_ENEMY)
		{
			/* Only draw if within visible minimap bounds */
			if (current->pos_x >= 0 && current->pos_x < max_visible &&
				current->pos_y >= 0 && current->pos_y < max_visible)
			{
				pixel_x = start_x + ((int)current->pos_x * MINIMAP_SCALE);
				pixel_y = start_y + ((int)current->pos_y * MINIMAP_SCALE);
				
				/* Color based on object type */
				if (current->type == OBJ_DOOR)
					color = 0x00FF00;
				else if (current->type == OBJ_HEALTH)
					color = 0xFF0000;
				else if (current->type == OBJ_AMMO)
					color = 0xFFFF00;
				else if (current->type == OBJ_KEY)
					color = 0x00FFFF;
				else
					color = 0xFFFFFF;
				
				/* Draw as 2x2 square */
				minimap_draw_rect(img, pixel_x, pixel_y, 2, 2, color);
			}
		}
		current = current->next;
	}
}

/*
** Main minimap rendering function
** Draws complete 2D top-down view of level
*/
void	render_minimap(t_game *game, t_img *img)
{
	if (!game || !img)
		return ;
	
	draw_minimap_background(game, img);
	draw_minimap_walls(game, img);
	draw_minimap_objects(game, img);
	draw_minimap_enemies(game, img);
	draw_minimap_player(game, img);
}

/*
** Toggle minimap visibility
** Can be called when user presses 'M' key
*/
void	toggle_minimap(t_game *game)
{
	if (!game)
		return ;
	game->show_minimap = !(game->show_minimap);
}
