#include "../../includes/cub3d.h"


// Up = 65362, Down = 65364, Left = 65361, Right = 65363

int is_wall(t_game *game, double x, double y)
{

    int new_x = (int)(x);
    int new_y = (int)(y);

    if(new_x < 0 || new_y < 0 || new_y >= game->map->height || game->map->width <= new_x)
        return 1; 
    // printf("%c\n", game->map->map_arr[new_y][new_x]);
    // printf("%d\n , %d")
    if(game->map->map_arr[new_y][new_x] == '1')
        return 1;
    return 0;
}

// step of move 
int handl_move(int key, t_game *game)
{
    //printf("%d\n", key);
    double old_x;
    double old_y;
    old_x = game->player.x;
    old_y = game->player.y;
    if(key_up == key)
        game->player.y -= 0.1;
    else if(key_down == key)
        game->player.y += 0.1;
    else if(key_left == key)
        game->player.x -= 0.1;
    else if(key_right == key)
        game->player.x += 0.1;
    if(is_wall(game, game->player.x, game->player.y) == 1)
    {
        game->player.x = old_x;
        game->player.y = old_y;
    }
    draw(game, game->img);
    return 0;
}

// movment of the player
int move(t_game *game)
{
    mlx_key_hook(game->win, handl_move, game);
    return 0;
}