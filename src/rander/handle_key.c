/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:03:50 by mel-houa          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:36 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
	{
		if (game->menu.is_visible)
		{
			hide_menu(game);
			return (0);
		}
		close_and_free(game);
		exit(0);
	}
	else if (game->menu.is_visible)
	{
		if (keycode == KEY_UP)
			menu_select_prev(&game->menu);
		else if (keycode == KEY_DOWN)
			menu_select_next(&game->menu);
		else if (keycode == ' ' || keycode == 65293)
			menu_confirm(game);
		return (0);
	}
	else if (keycode == 'w' || keycode == KEY_UP)
		game->keys.w = 1;
	else if (keycode == 's' || keycode == KEY_DOWN)
		game->keys.s = 1;
	else if (keycode == 'a')
		game->keys.a = 1;
	else if (keycode == 'd')
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left_arrow = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right_arrow = 1;
	else if (keycode == E_KEY)
		check_object_interaction(game);
	else if (keycode == '1')
		switch_weapon(&game->weapon, WEAPON_PISTOL);
	else if (keycode == '2')
		switch_weapon(&game->weapon, WEAPON_SHOTGUN);
	else if (keycode == '3')
		switch_weapon(&game->weapon, WEAPON_RIFLE);
	else if (keycode == '4')
		switch_weapon(&game->weapon, WEAPON_SNIPER);
	else if (keycode == 'r')
		reload_weapon(&game->weapon);
	else if (keycode == ' ')
		fire_weapon(game);
	else if (keycode == 'm')
		toggle_minimap(game);
	else if (keycode == 'p')
		show_menu(game, MENU_PAUSE);
	return (0);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == KEY_UP)
		game->keys.w = 0;
	else if (keycode == 's' || keycode == KEY_DOWN)
		game->keys.s = 0;
	else if (keycode == 'a')
		game->keys.a = 0;
	else if (keycode == 'd')
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left_arrow = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right_arrow = 0;
	return (0);
}
