/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:53:10 by moirhira          #+#    #+#             */
/*   Updated: 2026/01/20 00:24:36 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libraries/get_line/get_line.h"
#include "../libraries/libft/libft.h"
#include "/usr/include/minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define KEY_DOWN 65364
#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define ESC_KEY 65307
#define WIN_TITLE "CUB3D"
#define E_KEY 101
#define MAX_OBJECTS 100
#define OBJECT_DISTANCE 1.0
#define PISTOL_DAMAGE 25
#define PISTOL_FIRE_RATE 15
#define PISTOL_SPREAD 0.05f
#define PISTOL_AMMO 60

#define SHOTGUN_DAMAGE 100
#define SHOTGUN_FIRE_RATE 18
#define SHOTGUN_SPREAD 0.3f
#define SHOTGUN_PELLETS 8
#define SHOTGUN_AMMO 30

#define RIFLE_DAMAGE 40
#define RIFLE_FIRE_RATE 8
#define RIFLE_SPREAD 0.01f
#define RIFLE_AMMO 90

#define SNIPER_DAMAGE 150
#define SNIPER_FIRE_RATE 30
#define SNIPER_SPREAD 0.0f
#define SNIPER_AMMO 20

#define BASE_RELOAD_TIME 60
#define ENEMY_DAMAGE 10

typedef enum e_weapon_type
{
	WEAPON_PISTOL,
	WEAPON_SHOTGUN,
	WEAPON_RIFLE,
	WEAPON_SNIPER,
} t_weapon_type;

typedef enum e_enemy_state
{
	ENEMY_IDLE,
	ENEMY_PATROL,
	ENEMY_CHASE,
	ENEMY_ATTACK,
	ENEMY_DEAD,
} t_enemy_state;

typedef enum e_enemy_type
{
	ENEMY_STATIONARY,
	ENEMY_MELEE,
	ENEMY_SNIPER,
	ENEMY_RUSHER,
	ENEMY_SUPPORT,
} t_enemy_type;

typedef struct s_weapon
{
	t_weapon_type current_weapon;
	int pistol_ammo;
	int shotgun_ammo;
	int rifle_ammo;
	int sniper_ammo;
	int max_pistol_ammo;
	int max_shotgun_ammo;
	int max_rifle_ammo;
	int max_sniper_ammo;
	int reload_time;
	int shoot_cooldown;
	int damage;
	int fire_rate;
	float spread;
	int projectiles;
	int switching;
	int switch_time;
} t_weapon;

typedef struct s_health
{
	int current_hp;
	int max_hp;
	int is_alive;
	int invulnerable_time;
	int damage_cooldown;
} t_health;

typedef enum e_skill_type
{
	SKILL_DAMAGE_BOOST,
	SKILL_HEALTH_BOOST,
	SKILL_AMMO_CAPACITY,
	SKILL_FIRE_RATE,
	SKILL_RELOAD_SPEED,
	SKILL_ACCURACY,
	SKILL_COUNT
} t_skill_type;

typedef struct s_skill
{
	t_skill_type type;
	int level;
	int max_level;
	float value;
} t_skill;

typedef struct s_progression
{
	int current_level;
	int current_xp;
	int xp_to_next_level;
	int total_xp;
	int skill_points;
	t_skill skills[SKILL_COUNT];
	int level_up_timer;
} t_progression;

typedef enum e_sound_type
{
	SOUND_PISTOL_FIRE,
	SOUND_SHOTGUN_FIRE,
	SOUND_RIFLE_FIRE,
	SOUND_SNIPER_FIRE,
	SOUND_RELOAD,
	SOUND_HIT,
	SOUND_LEVELUP,
	SOUND_DEATH,
	SOUND_COUNT
} t_sound_type;

typedef struct s_audio
{
	int enabled;
	float master_volume;
	float sfx_volume;
	float music_volume;
	int music_playing;
	int last_sfx_played;
} t_audio;

typedef struct s_texture
{
	void *img_ptr;
	char *addr;
	int width;
	int height;
	int bits_per_pixel;
	int size_line;
	int endian;
} t_texture;

typedef enum e_object_type
{
	OBJ_DOOR,
	OBJ_HEALTH,
	OBJ_AMMO,
	OBJ_KEY,
	OBJ_ENEMY,
	OBJ_SWITCH,
} t_object_type;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING,
} t_door_state;

typedef struct s_object
{
	t_object_type type;
	double pos_x;
	double pos_y;
	int state;
	char *texture_path;
	t_texture texture;
	int health;
	int ammo_count;
	int key_id;
	double scale;
	int visible;
	t_enemy_type enemy_type; /* subtype for OBJ_ENEMY */
	struct s_object *next;
} t_object;

typedef struct s_ray_hit
{
	double distance;
	double wall_x;
	int side;
	int map_x;
	int map_y;
} t_ray_hit;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	char dir;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double ray_dir_x;
	double ray_dir_y;
} t_player;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left_arrow;
	int right_arrow;
	int esc;
} t_keys;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int hex_color;
} t_color;

typedef struct s_map
{
	char **map_arr;
	int width;
	int height;
} t_map;

typedef struct s_image
{
	void *img_ptr;
	int bit_per_pixel;
	int size_line;
	int endian;
	char *img_pex_ptr;
} t_img;

/* Impact effects (blood, bullet holes, explosions) */
typedef struct s_impact
{
	double x;
	double y;
	int type;             /* 0=blood, 1=bullet hole, 2=explosion */
	int lifetime;         /* frames until disappearance */
	int texture_frame;    /* for animated impacts */
	struct s_impact *next;
} t_impact;

/* Floating damage indicators */
typedef struct s_damage_indicator
{
	double x;
	double y;
	int value;
	int lifetime;         /* frames remaining */
	double vy;            /* vertical velocity for float-up */
	struct s_damage_indicator *next;
} t_damage_indicator;

/* Camera effects state */
typedef struct s_camera_effects
{
	float shake_amount;      /* current shake intensity */
	float shake_duration;    /* remaining shake time */
	float bob_amount;        /* head bob intensity */
	float tilt_amount;       /* strafing tilt intensity */
	float fov_multiplier;    /* zoom multiplier */
	int   shake_offset_x;    /* computed pixel offset X */
	int   shake_offset_y;    /* computed pixel offset Y */
	int   frame;
} t_camera_effects;

typedef struct s_particle
{
	double x;
	double y;
	double vx;
	double vy;
	int lifetime;
	int max_lifetime;
	int color;
	int size;
	struct s_particle *next;
} t_particle;

typedef struct s_light_source
{
	double x;
	double y;
	int intensity;
	int color;
	float radius;
	int pulsing;
	int pulse_speed;
	struct s_light_source *next;
} t_light_source;

typedef struct s_visual_effects
{
	t_particle *particles;
	t_light_source *lights;
	int bloom_enabled;
	float bloom_intensity;
	int color_grade;
} t_visual_effects;

typedef enum e_level_type
{
	LEVEL_FOREST = 0,
	LEVEL_INDUSTRIAL = 1,
	LEVEL_WASTELAND = 2,
	LEVEL_UNDERGROUND = 3,
	LEVEL_FORTRESS = 4,
	LEVEL_COUNT = 5
} t_level_type;

typedef struct s_level
{
	int level_number;
	t_level_type theme;
	char *map_path;
	char *name;
	int enemy_count;
	float difficulty_modifier;
	int floor_color;
	int ceiling_color;
	int completed;
	int completion_time;
	int kills;
} t_level;

typedef struct s_level_manager
{
	t_level levels[LEVEL_COUNT];
	int current_level;
	int total_levels_completed;
	int level_start_time;
	int level_active;
	int boss_defeated;
} t_level_manager;

typedef struct s_game_stats
{
	int total_kills;
	int total_damage_dealt;
	int total_damage_taken;
	int accuracy_percentage;
	int total_shots_fired;
	int total_shots_hit;
	int total_score;
	int playtime_seconds;
	int levels_completed;
	int new_game_plus_runs;
	int highest_level_reached;
	int current_multiplier;
} t_game_stats;

typedef enum e_menu_state
{
	MENU_NONE = 0,
	MENU_MAIN = 1,
	MENU_PAUSE = 2,
	MENU_GAME_OVER = 3,
	MENU_STATS = 4,
	MENU_NEW_GAME_PLUS = 5,
	MENU_QUIT = 6
} t_menu_state;

typedef struct s_menu
{
	t_menu_state state;
	int selected_option;
	int option_count;
	int is_visible;
	int animation_frame;
	int blink_frame;
} t_menu;

typedef struct s_game
{
	void *mlx;
	void *win;
	int scren_width;
	int scren_height;
	char *tex_paths[4];
	t_map *map;
	t_player player;
	t_color floor_color;
	t_img *img;
	t_color ceiling_color;
	t_keys keys;
	t_texture textures[4];
	double move_speed;
	double rot_speed;
	t_object *objects;
	int object_count;
	int interaction_cooldown;
	t_weapon weapon;
	t_health health;
	t_progression progression;
	t_audio audio;
	t_level_manager level_manager;
	t_game_stats stats;
	t_menu menu;
	int show_minimap;
	/* Effects */
	t_impact *impacts;
	t_damage_indicator *damage_indicators;
	t_camera_effects camera_fx;
	t_visual_effects visual_fx;
	int hit_marker_timer;   /* frames left to show hit marker */
	/* Damage direction indicator */
	float last_damage_angle;
	int damage_dir_timer;    /* frames left to show direction */
} t_game;

int draw(t_game *game, t_img *img);
void draw_ceiling_and_floor(t_game *game, t_img *img);
void camera(t_game *game);
int is_wall(t_game *game, double x, double y);
void put_pixel(int x, int y, t_img *img, int color);
t_ray_hit cast_ray(t_game *game, double ray_x, double ray_y);
int mini_map(t_game *game, t_img *img);
void draw_player(t_img *img, t_game *game, double x, double y);
int key_press_handler(int keycode, t_game *game);
int key_release_handler(int keycode, t_game *game);
void move_player(t_game *game);
void rotate_player(t_game *game);
int game_update(t_game *game);
int init_randring(t_game *game);
unsigned int get_texture_color(t_texture *texture, int tex_x, int tex_y);
int load_all_textures(t_game *game);

int parse(t_game *game, char *filedata);
int parse_objects(t_game *game, int fd, char *first_line);
int process_config_line(t_game *game, char *trimmed, int *parsed);
int handle_config_line(t_game *game, char *trimmed, int *parsed);
int read_map_lines(t_game *game, int fd, char *first_line);
int validate_file_extension(char *file, char *extension);
int parse_texture(char *path, char **dest);
int parse_color(char *path, t_color *dest);
int parse_map(t_game *game, int fd, char *first_line);
int validate_map(t_game *game);
int check_map_is_closed(t_game *game);
int is_dir(char *arg);
int is_all_digits(char *str);
int ft_isempty(char *str);
int is_player(char c);
int close_and_free(t_game *game);

/* Object system functions */
t_object *create_object(t_object_type type, double x, double y, char *texture);
int add_object(t_game *game, t_object *obj);
void free_objects(t_object *objects);
void update_objects(t_game *game);
void render_objects(t_game *game, t_img *img);
void check_object_interaction(t_game *game);
int load_object_texture(t_object *obj, void *mlx);
double get_object_distance(t_game *game, t_object *obj);
int object_collision(t_game *game, double x, double y);
void sort_objects_by_distance(t_object **objects, t_game *game);

/* Combat system functions */
void init_weapon_system(t_weapon *weapon);
int can_shoot(t_weapon *weapon);
void fire_weapon(t_game *game);
void switch_weapon(t_weapon *weapon, t_weapon_type new_weapon);
void reload_weapon(t_weapon *weapon);
void update_weapon(t_weapon *weapon);
void add_ammo(t_weapon *weapon, t_weapon_type type, int amount);
int get_current_ammo(t_weapon *weapon);
double raycast_hit(t_game *game);
int check_enemy_hit(t_game *game, double distance);
void damage_enemy(t_game *game, int damage);

/* Enemy system functions */
void update_enemy_state(t_object *enemy, t_game *game);
void update_stationary_enemy(t_object *enemy, t_game *game);
void update_patrol_enemy(t_object *enemy, t_game *game);
void update_sniper_enemy(t_object *enemy, t_game *game);
void update_rusher_enemy(t_object *enemy, t_game *game);
void update_support_enemy(t_object *enemy, t_game *game);
void update_enemies(t_game *game);
t_object *create_enemy(double x, double y, t_enemy_type type);
int is_enemy_threatening(t_object *enemy, t_game *game);
int count_alive_enemies(t_game *game);

/* AI behaviors utilities */
void ai_flank(t_object *enemy, t_player *player);
void ai_group_attack(t_object **enemies, int count, t_player *player);
void ai_use_environment(t_object *enemy, t_game *game);

/* Health system functions */
void init_health_system(t_health *health);
void damage_player(t_health *health, int damage_amount);
void heal_player(t_health *health, int heal_amount);
int get_health_percentage(t_health *health);
int is_player_alive(t_health *health);
void update_health(t_health *health);
void respawn_player(t_health *health);
void damage_enemy_health(t_object *enemy, int damage);
void heal_enemy(t_object *enemy, int heal_amount);
int is_player_invulnerable(t_health *health);
int get_damage_screen_shake(t_health *health);
int get_damage_color_tint(t_health *health);

/* Damage helpers */
void damage_player_from(t_game *game, double src_x, double src_y, int damage_amount);

/* HUD system functions */
void render_hud(t_game *game, t_img *img);
void render_health_bar(t_game *game, t_img *img);
void render_ammo_counter(t_game *game, t_img *img);
void render_crosshair(t_game *game, t_img *img);
void render_weapon_info(t_game *game, t_img *img);
void render_game_over(t_game *game, t_img *img);
void render_minimap(t_game *game, t_img *img);
void toggle_minimap(t_game *game);

/* Effects API */
void add_impact(t_game *game, double x, double y, int type);
void update_impacts(t_game *game);
void render_impacts(t_game *game, t_img *img);

void add_damage_indicator(t_game *game, double x, double y, int value);
void update_damage_indicators(t_game *game);
void render_damage_indicators(t_game *game, t_img *img);

void update_camera_effects(t_game *game);
void trigger_screen_shake(t_game *game, float amount, float duration);
void render_hit_marker(t_game *game, t_img *img);
void render_damage_direction(t_game *game, t_img *img);

/* Progression system */
void init_progression(t_progression *prog);
void add_xp(t_game *game, int xp_amount);
void level_up(t_game *game);
void apply_skill_upgrade(t_progression *prog, t_skill_type skill);
void update_progression(t_game *game);
void render_progression_hud(t_game *game, t_img *img);

/* Audio system */
void init_audio(t_audio *audio);
void play_sound(t_game *game, t_sound_type sound);
void set_master_volume(t_audio *audio, float volume);
void toggle_audio(t_audio *audio);
void update_audio(t_game *game);

/* Visual effects system */
void init_visual_effects(t_visual_effects *vfx);
void emit_particle(t_visual_effects *vfx, double x, double y, int count, int type);
void update_particles(t_visual_effects *vfx);
void render_particles(t_visual_effects *vfx, t_img *img);
void add_light_source(t_visual_effects *vfx, double x, double y, int intensity, int color);
void update_lights(t_visual_effects *vfx);
void render_dynamic_lighting(t_visual_effects *vfx, t_img *img);
void cleanup_visual_effects(t_visual_effects *vfx);

/* Level management system */
void init_level_manager(t_level_manager *lm);
void load_level(t_game *game, int level_num);
void next_level(t_game *game);
void complete_level(t_game *game);
void render_level_info(t_game *game, t_img *img);
int get_current_level_difficulty(t_game *game);

/* Replayability system */
void init_game_stats(t_game_stats *stats);
void update_game_stats(t_game *game);
int calculate_score(t_game *game);
void add_kill_score(t_game *game, int enemy_type);
void reset_stats_for_new_game_plus(t_game_stats *stats);
void render_stats_screen(t_game *game, t_img *img);
void track_shot_fired(t_game *game);
void track_shot_hit(t_game *game);

/* Menu system */
void init_menu(t_menu *menu);
void show_menu(t_game *game, t_menu_state state);
void hide_menu(t_game *game);
void menu_select_next(t_menu *menu);
void menu_select_prev(t_menu *menu);
int menu_confirm(t_game *game);
void render_menu(t_game *game, t_img *img);
void update_menu_animation(t_menu *menu);

#endif
