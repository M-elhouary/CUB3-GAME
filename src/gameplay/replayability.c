#include "../../includes/cub3d.h"
#include <stdlib.h>

void init_game_stats(t_game_stats *stats)
{
	if (!stats)
		return ;
	
	stats->total_kills = 0;
	stats->total_damage_dealt = 0;
	stats->total_damage_taken = 0;
	stats->accuracy_percentage = 100;
	stats->total_shots_fired = 0;
	stats->total_shots_hit = 0;
	stats->total_score = 0;
	stats->playtime_seconds = 0;
	stats->levels_completed = 0;
	stats->new_game_plus_runs = 0;
	stats->highest_level_reached = 1;
	stats->current_multiplier = 1;
}

void track_shot_fired(t_game *game)
{
	if (!game)
		return ;
	game->stats.total_shots_fired++;
}

void track_shot_hit(t_game *game)
{
	if (!game)
		return ;
	game->stats.total_shots_hit++;
}

void add_kill_score(t_game *game, int enemy_type)
{
	int base_score;
	int score_bonus;

	if (!game)
		return ;

	game->stats.total_kills++;

	/* Score based on enemy type */
	if (enemy_type == 0)
		base_score = 100;  /* Basic enemy */
	else if (enemy_type == 1)
		base_score = 150;  /* Ranged enemy */
	else if (enemy_type == 2)
		base_score = 200;  /* Sniper enemy */
	else if (enemy_type == 3)
		base_score = 250;  /* Support enemy */
	else
		base_score = 100;

	/* Apply difficulty multiplier and level multiplier */
	score_bonus = (int)(base_score * game->stats.current_multiplier * 
		(1.0f + game->level_manager.current_level * 0.2f));
	game->stats.total_score += score_bonus;
}

int calculate_score(t_game *game)
{
	int accuracy_bonus;
	int speed_bonus;
	int level_bonus;
	int total;

	if (!game)
		return (0);

	accuracy_bonus = 0;
	if (game->stats.total_shots_fired > 0)
	{
		game->stats.accuracy_percentage = (game->stats.total_shots_hit * 100) / 
			game->stats.total_shots_fired;
		if (game->stats.accuracy_percentage > 50)
			accuracy_bonus = (game->stats.accuracy_percentage - 50) * 5;
	}

	/* Bonus for fast completion (max 5000 points) */
	if (game->level_manager.level_start_time > 0 && game->level_manager.level_start_time < 600)
		speed_bonus = (600 - game->level_manager.level_start_time) * 2;
	else
		speed_bonus = 0;

	/* Level completion bonus */
	level_bonus = game->stats.levels_completed * 500;

	total = game->stats.total_score + accuracy_bonus + speed_bonus + level_bonus;
	return (total);
}

void update_game_stats(t_game *game)
{
	if (!game)
		return ;

	/* Track playtime */
	game->stats.playtime_seconds++;

	/* Update highest level reached */
	if (game->level_manager.current_level + 1 > game->stats.highest_level_reached)
		game->stats.highest_level_reached = game->level_manager.current_level + 1;

	/* Update level completion count */
	game->stats.levels_completed = game->level_manager.total_levels_completed;

	/* Update current multiplier based on new game+ runs */
	game->stats.current_multiplier = 1 + (game->stats.new_game_plus_runs * 0.25f);
}

void reset_stats_for_new_game_plus(t_game_stats *stats)
{
	int highest_level;
	int ngp_count;

	if (!stats)
		return ;

	highest_level = stats->highest_level_reached;
	ngp_count = stats->new_game_plus_runs;

	/* Reset gameplay stats but keep progress tracking */
	stats->total_kills = 0;
	stats->total_damage_dealt = 0;
	stats->total_damage_taken = 0;
	stats->accuracy_percentage = 100;
	stats->total_shots_fired = 0;
	stats->total_shots_hit = 0;
	stats->total_score = 0;
	stats->playtime_seconds = 0;
	stats->levels_completed = 0;
	
	/* Keep and increment new game+ count */
	stats->new_game_plus_runs = ngp_count + 1;
	stats->highest_level_reached = highest_level;
	stats->current_multiplier = 1 + (stats->new_game_plus_runs * 0.25f);
}

void render_stats_screen(t_game *game, t_img *img)
{
	if (!game || !img)
		return ;

	/* Stats display would include:
	 * - Total Score: calculate_score(game)
	 * - Total Kills: game->stats.total_kills
	 * - Accuracy: game->stats.accuracy_percentage %
	 * - Playtime: game->stats.playtime_seconds seconds
	 * - Levels Completed: game->stats.levels_completed / LEVEL_COUNT
	 * - New Game+ Runs: game->stats.new_game_plus_runs
	 * Text rendering requires additional implementation
	 */
}
