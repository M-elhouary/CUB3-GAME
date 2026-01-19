/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:00 by game-dev          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:37 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Initialize player weapon system
*/
void	init_weapon_system(t_weapon *weapon)
{
	if (!weapon)
		return ;
	weapon->current_weapon = WEAPON_PISTOL;
	weapon->pistol_ammo = PISTOL_AMMO;
	weapon->shotgun_ammo = SHOTGUN_AMMO;
	weapon->rifle_ammo = RIFLE_AMMO;
	weapon->sniper_ammo = SNIPER_AMMO;
	weapon->max_pistol_ammo = PISTOL_AMMO * 3;
	weapon->max_shotgun_ammo = SHOTGUN_AMMO * 3;
	weapon->max_rifle_ammo = RIFLE_AMMO * 3;
	weapon->max_sniper_ammo = SNIPER_AMMO * 3;
	weapon->reload_time = 0;
	weapon->shoot_cooldown = 0;
	weapon->damage = PISTOL_DAMAGE;
	weapon->fire_rate = PISTOL_FIRE_RATE;
	weapon->spread = PISTOL_SPREAD;
	weapon->projectiles = 1;
	weapon->switching = 0;
	weapon->switch_time = 0;
}

/*
** Check if player can shoot (cooldown and ammo check)
*/
int	can_shoot(t_weapon *weapon)
{
	if (!weapon || weapon->shoot_cooldown > 0 || weapon->switching)
		return (0);
	if (weapon->current_weapon == WEAPON_PISTOL)
		return (weapon->pistol_ammo > 0);
	else if (weapon->current_weapon == WEAPON_SHOTGUN)
		return (weapon->shotgun_ammo > 0);
	else if (weapon->current_weapon == WEAPON_RIFLE)
		return (weapon->rifle_ammo > 0);
	else if (weapon->current_weapon == WEAPON_SNIPER)
		return (weapon->sniper_ammo > 0);
	return (0);
}

/*
** Fire current weapon (consume ammo, start cooldown)
*/
void	fire_weapon(t_game *game)
{
	if (!game || !can_shoot(&game->weapon))
		return ;
	track_shot_fired(game);
	if (game->weapon.current_weapon == WEAPON_PISTOL)
	{
		game->weapon.pistol_ammo--;
		play_sound(game, SOUND_PISTOL_FIRE);
		emit_particle(&game->visual_fx, game->player.pos_x + game->player.dir_x * 2, 
			game->player.pos_y + game->player.dir_y * 2, 3, 1);  /* Spark */
	}
	else if (game->weapon.current_weapon == WEAPON_SHOTGUN)
	{
		game->weapon.shotgun_ammo--;
		play_sound(game, SOUND_SHOTGUN_FIRE);
		emit_particle(&game->visual_fx, game->player.pos_x + game->player.dir_x * 2, 
			game->player.pos_y + game->player.dir_y * 2, 6, 1);  /* More spark */
	}
	else if (game->weapon.current_weapon == WEAPON_RIFLE)
	{
		game->weapon.rifle_ammo--;
		play_sound(game, SOUND_RIFLE_FIRE);
		emit_particle(&game->visual_fx, game->player.pos_x + game->player.dir_x * 2, 
			game->player.pos_y + game->player.dir_y * 2, 4, 1);  /* Spark */
	}
	else if (game->weapon.current_weapon == WEAPON_SNIPER)
	{
		game->weapon.sniper_ammo--;
		play_sound(game, SOUND_SNIPER_FIRE);
		emit_particle(&game->visual_fx, game->player.pos_x + game->player.dir_x * 2, 
			game->player.pos_y + game->player.dir_y * 2, 2, 1);  /* Light spark */
	}
	game->weapon.shoot_cooldown = game->weapon.fire_rate;
}

/*
** Switch to another weapon
*/
void	switch_weapon(t_weapon *weapon, t_weapon_type new_weapon)
{
	if (!weapon || weapon->switching)
		return ;
	weapon->switching = 1;
	weapon->switch_time = 10;
	if (new_weapon == WEAPON_PISTOL)
	{
		weapon->current_weapon = WEAPON_PISTOL;
		weapon->damage = PISTOL_DAMAGE;
		weapon->fire_rate = PISTOL_FIRE_RATE;
		weapon->spread = PISTOL_SPREAD;
		weapon->projectiles = 1;
	}
	else if (new_weapon == WEAPON_SHOTGUN)
	{
		weapon->current_weapon = WEAPON_SHOTGUN;
		weapon->damage = SHOTGUN_DAMAGE;
		weapon->fire_rate = SHOTGUN_FIRE_RATE;
		weapon->spread = SHOTGUN_SPREAD;
		weapon->projectiles = SHOTGUN_PELLETS;
	}
	else if (new_weapon == WEAPON_RIFLE)
	{
		weapon->current_weapon = WEAPON_RIFLE;
		weapon->damage = RIFLE_DAMAGE;
		weapon->fire_rate = RIFLE_FIRE_RATE;
		weapon->spread = RIFLE_SPREAD;
		weapon->projectiles = 1;
	}
	else if (new_weapon == WEAPON_SNIPER)
	{
		weapon->current_weapon = WEAPON_SNIPER;
		weapon->damage = SNIPER_DAMAGE;
		weapon->fire_rate = SNIPER_FIRE_RATE;
		weapon->spread = SNIPER_SPREAD;
		weapon->projectiles = 1;
	}
}

/*
** Reload current weapon
*/
void	reload_weapon(t_weapon *weapon)
{
	int	needed;
	int	reload_duration;

	if (!weapon || weapon->reload_time > 0 || weapon->switching)
		return ;
	reload_duration = BASE_RELOAD_TIME;
	if (weapon->current_weapon == WEAPON_PISTOL)
	{
		needed = weapon->max_pistol_ammo - weapon->pistol_ammo;
		if (needed > 0)
		{
			weapon->pistol_ammo = weapon->max_pistol_ammo;
			weapon->reload_time = reload_duration;
		}
	}
	else if (weapon->current_weapon == WEAPON_SHOTGUN)
	{
		needed = weapon->max_shotgun_ammo - weapon->shotgun_ammo;
		if (needed > 0)
		{
			weapon->shotgun_ammo = weapon->max_shotgun_ammo;
			weapon->reload_time = reload_duration + 15;
		}
	}
	else if (weapon->current_weapon == WEAPON_RIFLE)
	{
		needed = weapon->max_rifle_ammo - weapon->rifle_ammo;
		if (needed > 0)
		{
			weapon->rifle_ammo = weapon->max_rifle_ammo;
			weapon->reload_time = reload_duration - 10;
		}
	}
	else if (weapon->current_weapon == WEAPON_SNIPER)
	{
		needed = weapon->max_sniper_ammo - weapon->sniper_ammo;
		if (needed > 0)
		{
			weapon->sniper_ammo = weapon->max_sniper_ammo;
			weapon->reload_time = reload_duration + 30;
		}
	}
}

/*
** Update weapon state (cooldowns, reload time, switching)
*/
void	update_weapon(t_weapon *weapon)
{
	if (!weapon)
		return ;
	if (weapon->shoot_cooldown > 0)
		weapon->shoot_cooldown--;
	if (weapon->reload_time > 0)
		weapon->reload_time--;
	if (weapon->switching)
	{
		if (weapon->switch_time > 0)
			weapon->switch_time--;
		else
			weapon->switching = 0;
	}
}

/*
** Add ammo to inventory
*/
void	add_ammo(t_weapon *weapon, t_weapon_type type, int amount)
{
	if (!weapon)
		return ;
	if (type == WEAPON_PISTOL)
	{
		weapon->pistol_ammo += amount;
		if (weapon->pistol_ammo > weapon->max_pistol_ammo)
			weapon->pistol_ammo = weapon->max_pistol_ammo;
	}
	else if (type == WEAPON_SHOTGUN)
	{
		weapon->shotgun_ammo += amount;
		if (weapon->shotgun_ammo > weapon->max_shotgun_ammo)
			weapon->shotgun_ammo = weapon->max_shotgun_ammo;
	}
	else if (type == WEAPON_RIFLE)
	{
		weapon->rifle_ammo += amount;
		if (weapon->rifle_ammo > weapon->max_rifle_ammo)
			weapon->rifle_ammo = weapon->max_rifle_ammo;
	}
	else if (type == WEAPON_SNIPER)
	{
		weapon->sniper_ammo += amount;
		if (weapon->sniper_ammo > weapon->max_sniper_ammo)
			weapon->sniper_ammo = weapon->max_sniper_ammo;
	}
}

/*
** Get current ammo count
*/
int	get_current_ammo(t_weapon *weapon)
{
	if (!weapon)
		return (0);
	if (weapon->current_weapon == WEAPON_PISTOL)
		return (weapon->pistol_ammo);
	else if (weapon->current_weapon == WEAPON_SHOTGUN)
		return (weapon->shotgun_ammo);
	else if (weapon->current_weapon == WEAPON_RIFLE)
		return (weapon->rifle_ammo);
	else if (weapon->current_weapon == WEAPON_SNIPER)
		return (weapon->sniper_ammo);
	return (0);
}

/*
** Perform raycasting to detect if a shot hits a target
** Returns distance to closest hit, or -1 if no hit
*/
double	raycast_hit(t_game *game)
{
	t_ray_hit	hit;
	double		min_dist;
	double		max_dist;

	if (!game)
		return (-1.0);
	max_dist = 50.0;
	min_dist = max_dist;
	hit = cast_ray(game, game->player.dir_x, game->player.dir_y);
	if (hit.distance > 0.0 && hit.distance < min_dist)
		min_dist = hit.distance;
	return (min_dist < max_dist ? min_dist : -1.0);
}

/*
** Check for hit on enemies within firing cone
*/
int	check_enemy_hit(t_game *game, double distance)
{
	t_object	*current;
	double		dist_to_enemy;
	double		angle_to_enemy;
	double		player_angle;
	double		angle_diff;

	if (!game || distance < 0)
		return (0);
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	current = game->objects;
	while (current)
	{
		if (current->type == OBJ_ENEMY && current->visible && current->health > 0)
		{
			dist_to_enemy = sqrt(pow(current->pos_x - game->player.pos_x, 2) +
					pow(current->pos_y - game->player.pos_y, 2));
			if (dist_to_enemy > 0 && dist_to_enemy <= distance)
			{
				angle_to_enemy = atan2(current->pos_y - game->player.pos_y,
						current->pos_x - game->player.pos_x);
				angle_diff = fabs(player_angle - angle_to_enemy);
				while (angle_diff > M_PI)
					angle_diff -= M_PI;
				if (angle_diff < 0.3)
					return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

/*
** Damage nearest enemy in firing direction with spread support
** Handles both single shots and multi-projectile weapons like shotgun
*/
void	damage_enemy(t_game *game, int damage)
{
	t_object	*current;
	double		min_dist;
	t_object	*target;
	double		dist;
	double		angle_to_enemy;
	double		player_angle;
	double		angle_diff;
	int			i;
	double		spread_angle;
	double		cone_width;
	double		fx;
	double		fy;

	if (!game || damage <= 0)
		return ;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	cone_width = 0.3;
	if (game->weapon.current_weapon == WEAPON_SHOTGUN)
		cone_width = 0.5;
	else if (game->weapon.current_weapon == WEAPON_SNIPER)
		cone_width = 0.1;
	for (i = 0; i < game->weapon.projectiles; i++)
	{
		spread_angle = (game->weapon.spread * (i - game->weapon.projectiles / 2.0));
		min_dist = 9999.0;
		target = NULL;
		current = game->objects;
		while (current)
		{
			if (current->type == OBJ_ENEMY && current->visible && current->health > 0)
			{
				dist = sqrt(pow(current->pos_x - game->player.pos_x, 2) +
						pow(current->pos_y - game->player.pos_y, 2));
				if (dist > 0 && dist < 50.0)
				{
					angle_to_enemy = atan2(current->pos_y - game->player.pos_y,
							current->pos_x - game->player.pos_x);
					angle_diff = fabs(player_angle + spread_angle - angle_to_enemy);
					while (angle_diff > M_PI)
						angle_diff -= M_PI;
					if (angle_diff < cone_width && dist < min_dist)
					{
						min_dist = dist;
						target = current;
					}
				}
			}
			current = current->next;
		}
		if (target)
		{
			fx = target->pos_x;
			fy = target->pos_y;
			target->health -= damage;
			game->stats.total_damage_dealt += damage;
			add_impact(game, fx, fy, 0);
			add_damage_indicator(game, fx, fy, damage);
			trigger_screen_shake(game, 8.0f, 10.0f);
			play_sound(game, SOUND_HIT);
			emit_particle(&game->visual_fx, fx, fy, 8, 0);  /* Blood spray */
		}
	}
}
