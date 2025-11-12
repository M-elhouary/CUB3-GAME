/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 22:02:41 by moirhira          #+#    #+#             */
/*   Updated: 2025/11/11 21:58:09 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


// Load a single texture from file
static int load_texture(t_game *game, int index)
{
        t_texture *tex;

        // Get the texture struct for this index
        // we have 4 textures: 0-North, 1-South, 2-West, 3-East
        tex = &game->textures[index];
        // this function loads an XPM image file into an MLX image
        //retuns a pointer to the image or NULL if it fails
        //we also get the width and height of the image and 
        tex->img_ptr = mlx_xpm_file_to_image(game->mlx, game->tex_paths[index], &tex->width, &tex->height);
        if (!tex->img_ptr)
        {
                {
                        printf("Error: Failed to load texture: %s\n", game->tex_paths[index]);
                        return (0);
                }
        }
        // Get the address of the image data
        // returns a pointer to the image data
        // we also get bits_per_pixel, size_line, and endian info
        // which are needed to manipulate the image data directly
        // and store it in our texture struct
        tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel, &tex->size_line, &tex->endian);
        if (!tex->addr)
        {
                printf("Error: mlx_get_data_addr failed for texture.\n");
                mlx_destroy_image(game->mlx, tex->img_ptr);
                return (0);
        }
        return (1);
}

// Load all textures 4 textures North, South, West, East
int load_all_textures(t_game *game)
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
                                // for cleanup in case of failure
                                // release any previously loaded textures
                                // return 0 to indicate failure
                                // take tow parameters: MLX instance and image pointer
                                mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
                        }
                        return (0);
                }
                i++;
        }
        return (1);
}