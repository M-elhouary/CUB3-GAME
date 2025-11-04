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
    int dy = -4;
    while (dy < 5)
    {
        dx = -4;
        while (dx < 5)
        {
            put_pixel( (int)(x * 40 )+ (dx), (int)(y * 40 )+ (dy), img, 0x27F5F2);
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
        put_pixel((int)(x * 40), (int)(y * 40), img, 0xFF0000);
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
    int screen_x;
    int y;
    double ray_x;
    double ray_y;
    double distance;
    int wall_height;
    int start_y;
    int end_y;
    double t;

    // PART 1: Clear screen - Fill ceiling (top half)
    y = 0;
    while (y < game->scren_height / 2)
    {
        screen_x = 0;
        while (screen_x < game->scren_width)
        {
            put_pixel(screen_x, y, img, 0x5fc5e0);  // ceiling color
            screen_x++;
        }
        y++;
    }

    // PART 2: Clear screen - Fill floor (bottom half)
    while (y < game->scren_height)
    {
        screen_x = 0;
        while (screen_x < game->scren_width)
        {
            put_pixel(screen_x, y, img, 0x665e5c);  // floor color
            screen_x++;
        }
        y++;
    }

    // PART 3: Raycasting loop - One ray per screen column
    screen_x = 0;
    while (screen_x < game->scren_width)
    {
        // Calculate t (0.0 to 1.0) for this screen column
        t = (double)screen_x / game->scren_width;

        // Calculate ray direction for this column
        ray_x = game->player.dir_x + (game->player.plan_x * t);
        ray_y = game->player.dir_y + (game->player.plan_y * t);

        // Cast ray and get distance to wall
        distance = cast_ray(game, ray_x, ray_y);

        // Calculate wall height based on distance
        wall_height = (int)(game->scren_height / distance);

        // Clamp wall height to screen
        if (wall_height > game->scren_height)
            wall_height = game->scren_height;

        // Calculate where to start drawing (center vertically)
        start_y = (game->scren_height - wall_height) / 2;
        end_y = start_y + wall_height;

        // Draw vertical line at this screen column
        y = start_y;
        while (y < end_y)
        {
            put_pixel(screen_x, y, img, 0x304f24);  // wall color
            y++;
        }

        screen_x++;
    }

    // PART 4: Optional - Draw player marker for debugging (can comment out later)
    draw_player(img, game, game->player.x, game->player.y);
    draw_player_dir(img, game, game->player.x, game->player.y);
\

    // PART 5: Display on screen
    mlx_put_image_to_window(game->mlx, game->win, img->img_ptr, 0, 0);

    return 0;
}

 