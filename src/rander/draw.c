#include "../../includes/cub3d.h"



void put_pixel(int x, int y, t_img *img, int color)
{
    int offset;
    offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
    *(unsigned int *)(img->img_pex_ptr + offset) = color;
}

void draw_ceiling(t_img *img, t_game *game, int x, int y)
{

    put_pixel(x, y, img, 0xfb542b);
}
void draw_floor(t_img *img, t_game *game, int x, int y)
{
    put_pixel(x, y, img, 0xfbf82b);
}


void draw_wall(t_img *img, t_game *game, int x, int y)
{
    int dx = 0;
    int dy = 0;
    while (dy < 40)
    {
        write(1, "++++", 4);
        while (dx < 40)
        {
            put_pixel(x * 40 + dx, y * 40 + dy, img, 0x2b41fb);
            dx++;
        }
        dy++;
    }
}

int draw(t_game *game, t_img *img)
{
        
    int y, x;
    y = 0;
    x = 0;
    
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            
            if(y < WIN_HEIGHT / 2)
                draw_ceiling(img, game, x, y);
            else
            {
 
                if(y < game->map->height && x < game->map->width && game->map->map_arr[y][x] == '1')
                {
                    draw_wall(img, game, x, y);
                }
                else
                    draw_floor(img, game, x, y);
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
    // test    
    return 0;
}

