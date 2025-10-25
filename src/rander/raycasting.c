#include "../../includes/cub3d.h"



// Set initial direction and camera plane based on player starting orientation
void camera(t_game *game)
{

// NORTH DIRECTION AND PLANE
    if (game->player.dir == 'N')  // NORTH DIRECTION AND PLANE
    {
            game->player.dir_x = 0;
            game->player.dir_y = -1;
            game->player.plan_x = 0.66;
            game->player.plan_y = 0;
    }
    else if (game->player.dir == 'E')    // EAST DIRECTION AND PLANE
    {
        game->player.dir_x = 1;
        game->player.dir_y= 0; 
        game->player.plan_x = 0;
        game->player.plan_y = 0.66;
    }
    else if (game->player.dir == 'S')  // SOUTH DIRECTION AND PLANE
    {
        game->player.dir_x = 0;
        game->player.dir_y= 1;
        game->player.plan_x = -0.66;
        game->player.plan_y = 0;
    }
    else if (game->player.dir == 'W')  // WEST DIRECTION AND PLANE
    {
        game->player.dir_x = -1;
        game->player.dir_y= 0;
        game->player.plan_x = 0;
        game->player.plan_y = -0.66;
}





}




// check Vector Perpendicularity
// double dot_product = (dir_x * plane_x) + (dir_y * plane_y);
// printf("Dot product: %f (should be 0)\n", dot_product);

int cast()
{
    


}