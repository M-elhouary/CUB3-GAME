/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 22:02:41 by moirhira          #+#    #+#             */
/*   Updated: 2025/11/19 22:59:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_texture(t_game *game, int index)
{
	t_texture	*tex;

	tex = &game->textures[index];
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, game->tex_paths[index],
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		{
			printf("Error: Failed to load texture: %s\n",
				game->tex_paths[index]);
			return (0);
		}
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
			&tex->size_line, &tex->endian);
	if (!tex->addr)
	{
		printf("Error: mlx_get_data_addr failed for texture.\n");
		mlx_destroy_image(game->mlx, tex->img_ptr);
		return (0);
	}
	return (1);
}

int	load_all_textures(t_game *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (!load_texture(game, i))
		{
			while (i > 0)
			{
				i--;
				mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
			}
			return (0);
		}
		i++;
	}
	return (1);
}