#include "../../includes/cub3d.h"

static void	safe_put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (!img || x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
	if (offset < 0 || offset >= 1920 * 1080 * 4)
		return ;
	*(int *)(img->img_pex_ptr + offset) = color;
}

static void	draw_h_line(t_img *img, int x1, int x2, int y, int color)
{
	int	x;

	if (x1 > x2)
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}
	x = x1;
	while (x <= x2)
	{
		safe_put_pixel(img, x, y, color);
		x++;
	}
}

static void	draw_v_line(t_img *img, int x, int y1, int y2, int color)
{
	int	y;

	if (y1 > y2)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	y = y1;
	while (y <= y2)
	{
		safe_put_pixel(img, x, y, color);
		y++;
	}
}

static void	draw_filled_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			safe_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	init_progression(t_progression *prog)
{
	int	i;

	if (!prog)
		return ;
	prog->current_level = 1;
	prog->current_xp = 0;
	prog->xp_to_next_level = 100;
	prog->total_xp = 0;
	prog->skill_points = 0;
	prog->level_up_timer = 0;
	i = 0;
	while (i < SKILL_COUNT)
	{
		prog->skills[i].type = i;
		prog->skills[i].level = 0;
		prog->skills[i].max_level = 5;
		prog->skills[i].value = 1.0f;
		i++;
	}
}

static int	get_xp_for_level(int level)
{
	return (100 + (level - 1) * 50);
}

void	add_xp(t_game *game, int xp_amount)
{
	if (!game || xp_amount <= 0)
		return ;
	game->progression.current_xp += xp_amount;
	game->progression.total_xp += xp_amount;
	while (game->progression.current_xp >= game->progression.xp_to_next_level)
	{
		game->progression.current_xp -= game->progression.xp_to_next_level;
		level_up(game);
	}
}

void	level_up(t_game *game)
{
	if (!game)
		return ;
	game->progression.current_level++;
	game->progression.skill_points++;
	game->progression.xp_to_next_level = get_xp_for_level(game->progression.current_level);
	game->progression.level_up_timer = 120;
	trigger_screen_shake(game, 15.0f, 20.0f);
	play_sound(game, SOUND_LEVELUP);
	emit_particle(&game->visual_fx, game->player.pos_x, game->player.pos_y, 12, 3);  /* Fire particles */
	add_light_source(&game->visual_fx, game->player.pos_x, game->player.pos_y, 100, 0xFF00FF);
}

void	apply_skill_upgrade(t_progression *prog, t_skill_type skill)
{
	if (!prog || skill < 0 || skill >= SKILL_COUNT)
		return ;
	if (prog->skill_points <= 0)
		return ;
	if (prog->skills[skill].level >= prog->skills[skill].max_level)
		return ;
	prog->skills[skill].level++;
	prog->skill_points--;
	if (skill == SKILL_DAMAGE_BOOST)
		prog->skills[skill].value = 1.0f + (prog->skills[skill].level * 0.1f);
}

void	update_progression(t_game *game)
{
	if (!game)
		return ;
	if (game->progression.level_up_timer > 0)
		game->progression.level_up_timer--;
}

void	render_progression_hud(t_game *game, t_img *img)
{
	int	x_pos;
	int	y_pos;
	int	bar_width;
	int	filled_width;
	int	color;

	if (!game || !img)
		return ;
	x_pos = 10;
	y_pos = 10;
	bar_width = 200;
	filled_width = (int)((double)game->progression.current_xp / 
		game->progression.xp_to_next_level * bar_width);
	if (filled_width > bar_width)
		filled_width = bar_width;
	draw_filled_rect(img, x_pos, y_pos, bar_width, 15, 0x111111);
	draw_filled_rect(img, x_pos, y_pos, filled_width, 15, 0x00FF00);
	draw_h_line(img, x_pos, x_pos + bar_width, y_pos, 0xFFFFFF);
	draw_h_line(img, x_pos, x_pos + bar_width, y_pos + 15, 0xFFFFFF);
	draw_v_line(img, x_pos, y_pos, y_pos + 15, 0xFFFFFF);
	draw_v_line(img, x_pos + bar_width, y_pos, y_pos + 15, 0xFFFFFF);
	draw_filled_rect(img, x_pos - 25, y_pos, 20, 15, 0x4444FF);
	if (game->progression.skill_points > 0)
		draw_filled_rect(img, x_pos + bar_width + 10, y_pos, 20, 15, 0xFFFF00);
	if (game->progression.level_up_timer > 0)
	{
		color = (game->progression.level_up_timer > 60) ? 0xFFFFFF : 0xFF00FF;
		draw_h_line(img, 0, img->bit_per_pixel, 0, color);
	}
}
