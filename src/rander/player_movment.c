#include "../../includes/cub3d.h"



// Up = 65362, Down = 65364, Left = 65361, Right = 65363


int handl_move(int key, t_game *game)
{
    printf("%d\n", key);
    if(key_up == key)
        game->player.y -= 0.9;
    else if(key_down == key)
        game->player.y += 0.9;
    else if(key_left == key)
        game->player.x -= 0.9;
    else if(key_right == key)
        game->player.x += 0.9;
    draw(game, game->img);
    return 0;
}


int move(t_game *game)
{
    mlx_key_hook(game->win, handl_move, game);
    return 0;
}