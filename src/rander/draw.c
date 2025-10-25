#include "../../includes/cub3d.h"


void put_pixel(int x, int y, t_img *img, int color)
{
    int offset;
    offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
    *(unsigned int *)(img->img_pex_ptr + offset) = color;
}


void draw_ceiling(t_img *img, t_game *game, int x, int y)
{
    int dx;
    int dy = 0;
    while (dy < 40)
    {
        dx = 0;
        while (dx < 40)
        {
                put_pixel(x * 40 + dx, y * 40 + dy, img, 0xfb2b);
                dx++;
        }
        dy++;
    }
}
void draw_floor(t_img *img, t_game *game, int x, int y)
{
    int dx;
    int dy = 0;
    while (dy < 40)
    {
        dx = 0;
        while (dx < 40)
        {
                put_pixel(x * 40 + dx, y * 40 + dy, img, 0xfbf82b);
                dx++;
        }
        dy++;
    }
}


void draw_wall(t_img *img, t_game *game, int x, int y)
{
    int dx;
    int dy = 0;
    while (dy < 40)
    {
        dx = 0;
        while (dx < 40)
        {
            put_pixel((x * 40 + dx), y * 40 + dy, img, 0x2b41fb);
            dx++;
        }
        dy++;
    }
}
void draw_player(t_img *img, t_game *game, double x, double y)
{
    int dx;
    int dy = 0;
    while (dy < 20)
    {
        dx = 0;
        while (dx < 20)
        {
            put_pixel( (int)(x * 40 + dx + 10), (int)(y * 40 + dy + 10), img, 0x27F5F2);
            dx++;
        }
        dy++;
    }
}


void draw_player_dir(t_img *img, t_game *game, double x, double y)
{

    double length = 0.90;    // length in tiles for the direction line
    double step = 0.01;     // step in tiles
    int steps = (int)(length / step);
    for (int i = 0; i <= steps; ++i)
    {
        put_pixel((int)(x * 40 + 20), (int)(y * 40 + 20), img, 0xFF0000);
        x += (double)game->player.dir_x * step;
        y += (double)game->player.dir_y * step;
    }
}

int check_player(char player)
{
    return(player == 'W' || player == 'N' || player == 'E' || player == 'S');
}

int draw(t_game *game, t_img *img)
{
        
    int y, x;
    y = 0;
    x = 0;
    
    while (y <  game->height)
    {
        x = 0;
        while (x < game->width)
        {
                if(y < game->map->height && x < game->map->width && game->map->map_arr[y][x] == '1')
                    draw_wall(img, game, x, y);
                else if(y < game->map->height && x < game->map->width && ( game->map->map_arr[y][x] == '0' || check_player(game->map->map_arr[y][x])))
                     draw_floor(img, game, x, y);
                else if (y < game->map->height && x < game->map->width && game->map->map_arr[y][x] == ' ')
                         draw_ceiling(img, game, x, y);
            x++;
        }
        y++;
    }
    // printf("player pos : x= %.2f , y= %.2f \n", game->player.x, game->player.y);
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
               if(y < game->map->height && x < game->map->width && check_player(game->map->map_arr[y][x]))
                         draw_player(img, game, game->player.x, game->player.y);
            x++;
        }
        y++;
    }
    draw_player_dir(img, game, game->player.x, game->player.y);
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);
    return 0;
}

