/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/19 20:32:38 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Simple 5x7 bitmap font for digit rendering
** Each digit stored as 7-bit wide array
*/
static const int	digit_font[10][7] = {
	{0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110},
	{0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110},
	{0b01110, 0b10001, 0b00001, 0b00110, 0b01000, 0b10000, 0b11111},
	{0b01110, 0b10001, 0b00001, 0b00110, 0b00001, 0b10001, 0b01110},
	{0b00010, 0b00110, 0b01010, 0b10010, 0b11111, 0b00010, 0b00010},
	{0b11111, 0b10000, 0b11110, 0b00001, 0b00001, 0b10001, 0b01110},
	{0b01110, 0b10001, 0b10000, 0b11110, 0b10001, 0b10001, 0b01110},
	{0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b10000},
	{0b01110, 0b10001, 0b10001, 0b01110, 0b10001, 0b10001, 0b01110},
	{0b01110, 0b10001, 0b10001, 0b01111, 0b00001, 0b10001, 0b01110},
};

/*
** Draw a single digit at specified position
** size: scale factor (1 = 5x7, 2 = 10x14, etc)
*/
static void	draw_digit(t_img *img, int digit, int x, int y, int size, int color)
{
	int	row;
	int	col;
	int	bit;
	int	draw_x;
	int	draw_y;

	if (digit < 0 || digit > 9 || !img)
		return ;
	row = 0;
	while (row < 7)
	{
		col = 0;
		while (col < 5)
		{
			bit = (digit_font[digit][row] >> (4 - col)) & 1;
			if (bit)
			{
				draw_x = x + (col * size);
				draw_y = y + (row * size);
				int	i = 0;
				while (i < size)
				{
					int	j = 0;
					while (j < size)
					{
						put_pixel(draw_x + j, draw_y + i, img, color);
						j++;
					}
					i++;
				}
			}
			col++;
		}
		row++;
	}
}

/*
** Draw a number (converts to string then renders each digit)
** x, y: starting position
** size: scale factor for digits
** color: text color
*/
void	draw_number(t_img *img, int number, int x, int y, int size, int color)
{
	char	buffer[16];
	int		len;
	int		i;
	int		digit;

	if (!img)
		return ;
	
	/* Handle negative numbers */
	if (number < 0)
	{
		number = -number;
		draw_digit(img, -1, x, y, size, color);
		x += (5 * size) + 2;
	}
	
	/* Convert number to string */
	if (number == 0)
	{
		draw_digit(img, 0, x, y, size, color);
		return ;
	}
	
	len = 0;
	while (number > 0)
	{
		buffer[len++] = (number % 10) + '0';
		number /= 10;
	}
	
	/* Draw digits in correct order (reverse) */
	i = len - 1;
	while (i >= 0)
	{
		digit = buffer[i] - '0';
		draw_digit(img, digit, x, y, size, color);
		x += (5 * size) + 2;
		i--;
	}
}

/*
** Draw "HEALTH: XX/100" text
*/
void	draw_health_text(t_game *game, t_img *img)
{
	int	health_percent;

	if (!game || !img)
		return ;
	health_percent = get_health_percentage(&game->health);
	
	/* Draw at position (30, 15) - next to health bar */
	draw_number(img, health_percent, 30, 15, 1, 0xFFFFFF);
}

/*
** Draw "AMMO: XX/YY" text
*/
void	draw_ammo_text(t_game *game, t_img *img)
{
	int	current_ammo;
	int	max_ammo;
	int	x_pos;

	if (!game || !img)
		return ;
	current_ammo = get_current_ammo(&game->weapon);
	if (game->weapon.current_weapon == WEAPON_PISTOL)
		max_ammo = game->weapon.max_pistol_ammo;
	else
		max_ammo = game->weapon.max_rifle_ammo;
	
	x_pos = img->bit_per_pixel - 140;
	
	/* Draw current ammo */
	draw_number(img, current_ammo, x_pos + 20, 15, 1, 0xFFFFFF);
}

/*
** Draw FPS number
*/
void	draw_fps_text(t_img *img, int fps)
{
	int	x_pos;
	int	y_pos;
	int	color;

	if (!img)
		return ;
	x_pos = img->bit_per_pixel - 90;
	y_pos = img->bit_per_pixel - 35;
	
	/* Color based on FPS */
	if (fps >= 50)
		color = 0x00FF00;
	else if (fps >= 30)
		color = 0xFFFF00;
	else
		color = 0xFF0000;
	
	draw_number(img, fps, x_pos + 10, y_pos + 5, 1, color);
}

/*
** Draw "WEAPON: PISTOL/RIFLE" indicator
*/
void	draw_weapon_indicator(t_game *game, t_img *img)
{
	int	x_pos;
	int	y_pos;
	int	color;

	if (!game || !img)
		return ;
	
	x_pos = img->bit_per_pixel / 2 - 40;
	y_pos = img->bit_per_pixel - 50;
	
	/* Color indicates weapon: Blue = Pistol, Red = Rifle */
	if (game->weapon.current_weapon == WEAPON_PISTOL)
		color = 0x0099FF;
	else
		color = 0xFF0000;
	
	/* Draw small indicator box */
	int	i = 0;
	while (i < 10)
	{
		put_pixel(x_pos + i, y_pos, img, color);
		put_pixel(x_pos + i, y_pos + 9, img, color);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		put_pixel(x_pos, y_pos + i, img, color);
		put_pixel(x_pos + 9, y_pos + i, img, color);
		i++;
	}
}

/*
** Draw game over screen
*/
void	draw_game_over_screen(t_img *img)
{
	int	i;
	int	j;

	if (!img)
		return ;
	
	/* Semi-transparent black overlay */
	i = 0;
	while (i < img->bit_per_pixel)
	{
		j = 0;
		while (j < img->bit_per_pixel)
		{
			put_pixel(j, i, img, 0x000000);
			j++;
		}
		i++;
	}
}

/*
** Draw objective/message text in center of screen
*/
void	draw_objective_text(t_img *img, const char *text, int color)
{
	int	x;
	int	y;

	if (!img || !text)
		return ;
	x = img->bit_per_pixel / 2 - 40;
	y = img->bit_per_pixel / 2;
	
	/* Text would be drawn here if we had a full font implementation */
	(void)x;
	(void)y;
	(void)color;
}

/*
** Main text rendering function
** Called once per frame to update all text elements
*/
void	render_text(t_game *game, t_img *img)
{
	if (!game || !img)
		return ;
	
	draw_health_text(game, img);
	draw_ammo_text(game, img);
	draw_fps_text(img, 60);
	draw_weapon_indicator(game, img);
}
