#include "../../includes/cub3d.h"

void	init_audio(t_audio *audio)
{
	if (!audio)
		return ;
	audio->enabled = 1;
	audio->master_volume = 1.0f;
	audio->sfx_volume = 0.8f;
	audio->music_volume = 0.6f;
	audio->music_playing = 0;
	audio->last_sfx_played = -1;
}

void	play_sound(t_game *game, t_sound_type sound)
{
	if (!game || !game->audio.enabled)
		return ;
	
	game->audio.last_sfx_played = sound;
}

void	set_master_volume(t_audio *audio, float volume)
{
	if (!audio)
		return ;
	if (volume < 0.0f)
		volume = 0.0f;
	if (volume > 1.0f)
		volume = 1.0f;
	audio->master_volume = volume;
}

void	toggle_audio(t_audio *audio)
{
	if (!audio)
		return ;
	audio->enabled = !audio->enabled;
}

void	update_audio(t_game *game)
{
	if (!game || !game->audio.enabled)
		return ;
}
