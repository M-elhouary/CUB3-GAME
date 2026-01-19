#include "../../includes/cub3d.h"
#include <stdlib.h>

void init_menu(t_menu *menu)
{
	if (!menu)
		return ;
	
	menu->state = MENU_NONE;
	menu->selected_option = 0;
	menu->option_count = 0;
	menu->is_visible = 0;
	menu->animation_frame = 0;
	menu->blink_frame = 0;
}

void show_menu(t_game *game, t_menu_state state)
{
	if (!game)
		return ;
	
	game->menu.state = state;
	game->menu.is_visible = 1;
	game->menu.animation_frame = 0;
	game->menu.selected_option = 0;
	
	/* Set option counts based on menu type */
	if (state == MENU_MAIN)
		game->menu.option_count = 3;  /* New Game, New Game+, Quit */
	else if (state == MENU_PAUSE)
		game->menu.option_count = 3;  /* Resume, Stats, Quit to Menu */
	else if (state == MENU_GAME_OVER)
		game->menu.option_count = 3;  /* Retry Level, New Game+, Main Menu */
	else if (state == MENU_NEW_GAME_PLUS)
		game->menu.option_count = 2;  /* Continue, Quit to Menu */
	else
		game->menu.option_count = 1;
}

void hide_menu(t_game *game)
{
	if (!game)
		return ;
	
	game->menu.state = MENU_NONE;
	game->menu.is_visible = 0;
	game->menu.animation_frame = 0;
}

void menu_select_next(t_menu *menu)
{
	if (!menu || menu->option_count <= 0)
		return ;
	
	menu->selected_option++;
	if (menu->selected_option >= menu->option_count)
		menu->selected_option = 0;
	menu->blink_frame = 0;
}

void menu_select_prev(t_menu *menu)
{
	if (!menu || menu->option_count <= 0)
		return ;
	
	menu->selected_option--;
	if (menu->selected_option < 0)
		menu->selected_option = menu->option_count - 1;
	menu->blink_frame = 0;
}

int menu_confirm(t_game *game)
{
	if (!game || !game->menu.is_visible)
		return (0);
	
	if (game->menu.state == MENU_MAIN)
	{
		if (game->menu.selected_option == 0)
		{
			/* New Game */
			hide_menu(game);
			return (1);  /* Start new game */
		}
		else if (game->menu.selected_option == 1)
		{
			/* New Game+ */
			show_menu(game, MENU_NEW_GAME_PLUS);
			return (0);
		}
		else if (game->menu.selected_option == 2)
		{
			/* Quit */
			return (-1);  /* Exit game */
		}
	}
	else if (game->menu.state == MENU_PAUSE)
	{
		if (game->menu.selected_option == 0)
		{
			/* Resume */
			hide_menu(game);
			return (1);
		}
		else if (game->menu.selected_option == 1)
		{
			/* Stats */
			show_menu(game, MENU_STATS);
			return (0);
		}
		else if (game->menu.selected_option == 2)
		{
			/* Quit to Menu */
			show_menu(game, MENU_MAIN);
			return (0);
		}
	}
	else if (game->menu.state == MENU_GAME_OVER)
	{
		if (game->menu.selected_option == 0)
		{
			/* Retry Level */
			hide_menu(game);
			return (1);
		}
		else if (game->menu.selected_option == 1)
		{
			/* New Game+ */
			show_menu(game, MENU_NEW_GAME_PLUS);
			return (0);
		}
		else if (game->menu.selected_option == 2)
		{
			/* Main Menu */
			show_menu(game, MENU_MAIN);
			return (0);
		}
	}
	else if (game->menu.state == MENU_NEW_GAME_PLUS)
	{
		if (game->menu.selected_option == 0)
		{
			/* Continue with NGP */
			hide_menu(game);
			reset_stats_for_new_game_plus(&game->stats);
			return (1);
		}
		else if (game->menu.selected_option == 1)
		{
			/* Back to Main Menu */
			show_menu(game, MENU_MAIN);
			return (0);
		}
	}
	else if (game->menu.state == MENU_STATS)
	{
		/* Return to previous menu on confirm */
		show_menu(game, MENU_PAUSE);
		return (0);
	}
	
	return (0);
}

void update_menu_animation(t_menu *menu)
{
	if (!menu || !menu->is_visible)
		return ;
	
	menu->animation_frame++;
	menu->blink_frame++;
	
	/* Reset blink at 30 frames */
	if (menu->blink_frame > 30)
		menu->blink_frame = 0;
}

static void draw_rect(int x, int y, int w, int h, int color, t_img *img)
{
	int i, j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			int offset = ((y + i) * img->size_line) + ((x + j) * (img->bit_per_pixel / 8));
			if (x + j >= 0 && x + j < 1920 && y + i >= 0 && y + i < 1080)
				*(unsigned int *)(img->img_pex_ptr + offset) = color;
			j++;
		}
		i++;
	}
}

void render_menu(t_game *game, t_img *img)
{
	int menu_y;
	int option_y;
	int i;

	if (!game || !img || !game->menu.is_visible)
		return ;

	/* Semi-transparent background overlay */
	draw_rect(0, 0, 1920, 1080, 0x000000, img);

	menu_y = 300;

	if (game->menu.state == MENU_MAIN)
	{
		/* Draw main menu options */
		option_y = menu_y;
		i = 0;
		while (i < 3)
		{
			int color = (i == game->menu.selected_option) ? 0xFF00FF : 0xFFFFFF;
			
			if (i == 0)
				draw_rect(800, option_y, 300, 40, color, img);  /* New Game */
			else if (i == 1)
				draw_rect(800, option_y, 300, 40, color, img);  /* New Game+ */
			else if (i == 2)
				draw_rect(800, option_y, 300, 40, color, img);  /* Quit */
			
			option_y += 80;
			i++;
		}
	}
	else if (game->menu.state == MENU_PAUSE)
	{
		/* Draw pause menu options */
		option_y = menu_y;
		i = 0;
		while (i < 3)
		{
			int color = (i == game->menu.selected_option) ? 0xFF00FF : 0xFFFFFF;
			draw_rect(800, option_y, 300, 40, color, img);
			option_y += 80;
			i++;
		}
	}
	else if (game->menu.state == MENU_GAME_OVER)
	{
		/* Draw game over menu options */
		option_y = menu_y;
		i = 0;
		while (i < 3)
		{
			int color = (i == game->menu.selected_option) ? 0xFF0000 : 0xFFFFFF;
			draw_rect(800, option_y, 300, 40, color, img);
			option_y += 80;
			i++;
		}
	}
	else if (game->menu.state == MENU_NEW_GAME_PLUS)
	{
		/* Draw NGP confirmation menu */
		option_y = menu_y;
		i = 0;
		while (i < 2)
		{
			int color = (i == game->menu.selected_option) ? 0x00FF00 : 0xFFFFFF;
			draw_rect(800, option_y, 300, 40, color, img);
			option_y += 80;
			i++;
		}
	}
	else if (game->menu.state == MENU_STATS)
	{
		/* Draw stats screen */
		draw_rect(200, 100, 1520, 880, 0x1a1a1a, img);
		/* Stats would be rendered here */
	}
}
