#include "../../includes/cub3d.h"



void camera(t_game *game)
{

    if (game->player.dir == 'N')
    {
            game->player.dir_x = 0;
            game->player.dir_y = -1;
            game->player.x = 0.66;
            game->player.y = 0;
    }
    else if (game->player.dir == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y= 0; 
        game->player.x = 0;
        game->player.y = 0.66;
    }
    else if (game->player.dir == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y= 1;
        game->player.x = -0.66;
        game->player.y = 0;
    }
    else if (game->player.dir == 'W') 
    {
        game->player.dir_x = -1;
        game->player.dir_y= 0;
        game->player.x = 0;
        game->player.y = -0.66;
}


}


int cast()
{
    


}