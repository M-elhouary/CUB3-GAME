/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Update enemy AI state machines
** Enemies can be in different states: idle, patrol, chase, attack, dead
*/
void	update_enemy_state(t_object *enemy, t_game *game)
{
	double	dist_to_player;
	int		can_see_player;

	if (!enemy || !game || enemy->type != OBJ_ENEMY)
		return ;
	dist_to_player = sqrt(pow(enemy->pos_x - game->player.pos_x, 2) +
			pow(enemy->pos_y - game->player.pos_y, 2));
	if (enemy->health <= 0)
	{
		if (enemy->state != ENEMY_DEAD)
		{
			int xp_reward = 50;
			int enemy_type_for_score = 0;
			if (enemy->enemy_type == ENEMY_SNIPER)
			{
				xp_reward = 100;
				enemy_type_for_score = 2;
			}
			else if (enemy->enemy_type == ENEMY_RUSHER)
			{
				xp_reward = 80;
				enemy_type_for_score = 0;
			}
			else if (enemy->enemy_type == ENEMY_SUPPORT)
			{
				xp_reward = 90;
				enemy_type_for_score = 3;
			}
			else
			{
				enemy_type_for_score = 1;
			}
			add_xp(game, xp_reward);
			track_shot_hit(game);
			add_kill_score(game, enemy_type_for_score);
		}
		enemy->state = ENEMY_DEAD;
		enemy->visible = 0;
		return ;
	}
	can_see_player = (dist_to_player < 15.0);
	if (can_see_player)
		enemy->state = ENEMY_CHASE;
	else
		enemy->state = ENEMY_PATROL;
}

/*
** Stationary shooter enemy AI
** Stays in place and shoots at player when nearby
*/
void	update_stationary_enemy(t_object *enemy, t_game *game)
{
	double	dist_to_player;

	if (!enemy || !game)
		return ;
	dist_to_player = sqrt(pow(enemy->pos_x - game->player.pos_x, 2) +
			pow(enemy->pos_y - game->player.pos_y, 2));
	if (dist_to_player < 20.0 && enemy->health > 0)
	{
		/* Enemy shoots at player */
		if (rand() % 100 < 30)
		{
			/* Damage player (will be implemented in health_system.c) */
		}
	}
}

/*
** Patrolling melee enemy AI
** Walks in pattern and chases player when spotted
*/
void	update_patrol_enemy(t_object *enemy, t_game *game)
{
	double	dist_to_player;
	double	angle_to_player;
	double	move_speed;

	if (!enemy || !game)
		return ;
	dist_to_player = sqrt(pow(enemy->pos_x - game->player.pos_x, 2) +
			pow(enemy->pos_y - game->player.pos_y, 2));
	if (dist_to_player < 15.0 && enemy->health > 0)
	{
		/* Chase player */
		angle_to_player = atan2(game->player.pos_y - enemy->pos_y,
				game->player.pos_x - enemy->pos_x);
		move_speed = 0.02;
		enemy->pos_x += cos(angle_to_player) * move_speed;
		enemy->pos_y += sin(angle_to_player) * move_speed;
		if (!is_wall(game, enemy->pos_x, enemy->pos_y))
		{
		}
		else
		{
			enemy->pos_x -= cos(angle_to_player) * move_speed;
			enemy->pos_y -= sin(angle_to_player) * move_speed;
		}
	}
	else
	{
		/* Patrol in pattern - simple back and forth */
		if (enemy->ammo_count == 0)
			enemy->ammo_count = 1;
		else
			enemy->ammo_count = 0;
		if (enemy->ammo_count)
		{
			enemy->pos_x += 0.01;
		}
		else
		{
			enemy->pos_x -= 0.01;
		}
	}
}

/*
** Update all enemies in the game
*/
void	update_enemies(t_game *game)
{
	t_object	*current;

	if (!game)
		return ;
	current = game->objects;
	while (current)
	{
		if (current->type == OBJ_ENEMY)
		{
			update_enemy_state(current, game);
			if (current->state == ENEMY_DEAD)
			{
				current->visible = 0;
			}
			else
			{
				if (current->enemy_type == ENEMY_STATIONARY)
					update_stationary_enemy(current, game);
				else if (current->enemy_type == ENEMY_MELEE)
					update_patrol_enemy(current, game);
				else if (current->enemy_type == ENEMY_SNIPER)
					update_sniper_enemy(current, game);
				else if (current->enemy_type == ENEMY_RUSHER)
					update_rusher_enemy(current, game);
				else if (current->enemy_type == ENEMY_SUPPORT)
					update_support_enemy(current, game);
			}
		}
		current = current->next;
	}
}

/*
** Create a new enemy object
*/
t_object	*create_enemy(double x, double y, t_enemy_type type)
{
	t_object	*enemy;

	enemy = (t_object *)ft_malloc(sizeof(t_object));
	if (!enemy)
		return (NULL);
	enemy->type = OBJ_ENEMY;
	enemy->pos_x = x;
	enemy->pos_y = y;
	enemy->state = ENEMY_PATROL;
	enemy->visible = 1;
	enemy->scale = 1.0;
	enemy->next = NULL;
	enemy->enemy_type = type;
	if (type == ENEMY_STATIONARY)
	{
		enemy->health = 30;
		enemy->ammo_count = 0;
		enemy->texture_path = ft_strdup("textures/enemy_stationary.xpm");
	}
	else if (type == ENEMY_MELEE)
	{
		enemy->health = 50;
		enemy->ammo_count = 0;
		enemy->texture_path = ft_strdup("textures/enemy_melee.xpm");
	}
	else if (type == ENEMY_SNIPER)
	{
		enemy->health = 40;
		enemy->ammo_count = 0;
		enemy->texture_path = ft_strdup("textures/enemy_sniper.xpm");
	}
	else if (type == ENEMY_RUSHER)
	{
		enemy->health = 35;
		enemy->ammo_count = 0;
		enemy->texture_path = ft_strdup("textures/enemy_rusher.xpm");
	}
	else if (type == ENEMY_SUPPORT)
	{
		enemy->health = 60;
		enemy->ammo_count = 0;
		enemy->texture_path = ft_strdup("textures/enemy_support.xpm");
	}
	return (enemy);
}

/*
** Check if enemy is threatening (close and alive)
*/
int	is_enemy_threatening(t_object *enemy, t_game *game)
{
	double	dist;

	if (!enemy || !game || enemy->type != OBJ_ENEMY || enemy->health <= 0)
		return (0);
	dist = sqrt(pow(enemy->pos_x - game->player.pos_x, 2) +
			pow(enemy->pos_y - game->player.pos_y, 2));
	return (dist < 10.0);
}

/*
** Get count of alive enemies
*/
int	count_alive_enemies(t_game *game)
{
	t_object	*current;
	int			count;

	if (!game)
		return (0);
	count = 0;
	current = game->objects;
	while (current)
	{
		if (current->type == OBJ_ENEMY && current->health > 0)
			count++;
		current = current->next;
	}
	return (count);
}

/*
** Sniper enemy: stays at long range, aims slowly, high damage, weak close
*/
void	update_sniper_enemy(t_object *enemy, t_game *game)
{
	double dist;
	double angle;
	if (!enemy || !game)
		return;
	dist = sqrt(pow(enemy->pos_x - game->player.pos_x, 2) +
				pow(enemy->pos_y - game->player.pos_y, 2));
	if (dist < 8.0)
	{
		/* retreat when too close */
		angle = atan2(enemy->pos_y - game->player.pos_y,
					  enemy->pos_x - game->player.pos_x);
		enemy->pos_x += cos(angle) * 0.015;
		enemy->pos_y += sin(angle) * 0.015;
		ai_use_environment(enemy, game);
	}
	else if (dist < 25.0)
	{
		/* use cover when at range */
		ai_use_environment(enemy, game);
		if (rand() % 100 < 5)
			damage_player_from(game, enemy->pos_x, enemy->pos_y, 25);
	}
}

/*
** Rusher enemy: fast movement, charges player, dodges shots
*/
void	update_rusher_enemy(t_object *enemy, t_game *game)
{
	double angle;
	double speed;
	double dist;
	if (!enemy || !game)
		return;
	dist = sqrt(pow(enemy->pos_x - game->player.pos_x, 2) +
			 pow(enemy->pos_y - game->player.pos_y, 2));
	speed = 0.04;
	angle = atan2(game->player.pos_y - enemy->pos_y,
				  game->player.pos_x - enemy->pos_x);
	enemy->pos_x += cos(angle) * speed;
	enemy->pos_y += sin(angle) * speed;
	enemy->pos_x += (rand() % 3 - 1) * 0.01;
	enemy->pos_y += (rand() % 3 - 1) * 0.01;
	ai_use_environment(enemy, game);
	if (dist < 1.2)
		damage_player_from(game, enemy->pos_x, enemy->pos_y, 12);
}

/*
** Support enemy: heals other enemies, uses cover, maintains distance
*/
void	update_support_enemy(t_object *enemy, t_game *game)
{
	t_object *cur;
	if (!enemy || !game)
		return;
	cur = game->objects;
	while (cur)
	{
		if (cur->type == OBJ_ENEMY && cur != enemy && cur->health > 0)
		{
			double d = sqrt(pow(cur->pos_x - enemy->pos_x, 2) +
							pow(cur->pos_y - enemy->pos_y, 2));
			if (d < 5.0 && rand() % 100 < 10)
				heal_enemy(cur, 2);
		}
		cur = cur->next;
	}
	/* use cover and drift back */
	ai_use_environment(enemy, game);
	enemy->pos_x -= 0.005;
}
