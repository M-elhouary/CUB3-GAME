/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:21:21 by mel-houa          #+#    #+#             */
/*   Updated: 2025/12/03 15:57:08 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_ceiling_and_floor(t_game *game, t_img *img)
{
	int	screen_x;
	int	y;

	y = 0;
	while (y < game->scren_height / 2)
	{
		screen_x = 0;
		while (screen_x < game->scren_width)
		{
			put_pixel(screen_x, y, img, game->ceiling_color.hex_color);
			screen_x++;
		}
		y++;
	}
	while (y < game->scren_height)
	{
		screen_x = 0;
		while (screen_x < game->scren_width)
		{
			put_pixel(screen_x, y, img, game->floor_color.hex_color);
			screen_x++;
		}
		y++;
	}
}

void	put_pixel(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
	*(unsigned int *)(img->img_pex_ptr + offset) = color;
}

unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char *dst;

	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0x0); // Return black if coordinates are out of bounds
	dst = texture->addr + (tex_y * texture->size_line + tex_x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}