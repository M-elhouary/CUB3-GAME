#include "../../includes/cub3d.h"
#include <stdlib.h>
#include <math.h>

void init_visual_effects(t_visual_effects *vfx)
{
	vfx->particles = NULL;
	vfx->lights = NULL;
	vfx->bloom_enabled = 1;
	vfx->bloom_intensity = 1.5f;
	vfx->color_grade = 0;
}

static int get_particle_color(int type)
{
	switch (type)
	{
		case 0: return 0xFF4444;  /* Blood red */
		case 1: return 0xFFDD44;  /* Spark yellow */
		case 2: return 0x4488FF;  /* Spark blue */
		case 3: return 0xFF8844;  /* Fire orange */
		default: return 0xFFFFFF; /* White */
	}
}

static double get_random_velocity(void)
{
	return ((double)(rand() % 100) / 100.0 - 0.5) * 2.0;
}

void emit_particle(t_visual_effects *vfx, double x, double y, int count, int type)
{
	t_particle *new_particle;
	int i;

	i = 0;
	while (i < count)
	{
		new_particle = (t_particle *)malloc(sizeof(t_particle));
		if (!new_particle)
			return ;
		
		new_particle->x = x;
		new_particle->y = y;
		new_particle->vx = get_random_velocity() * 3.0;
		new_particle->vy = get_random_velocity() * 3.0 - 1.5;
		new_particle->lifetime = 60;
		new_particle->max_lifetime = 60;
		new_particle->color = get_particle_color(type);
		new_particle->size = 2;
		new_particle->next = vfx->particles;
		vfx->particles = new_particle;
		i++;
	}
}

void update_particles(t_visual_effects *vfx)
{
	t_particle *current;
	t_particle *prev;

	prev = NULL;
	current = vfx->particles;
	
	while (current)
	{
		current->x += current->vx;
		current->y += current->vy;
		current->vy += 0.1;  /* Gravity */
		current->lifetime--;
		current->size = (int)(2.0 * current->lifetime / current->max_lifetime);
		if (current->size < 1)
			current->size = 1;

		if (current->lifetime <= 0)
		{
			if (prev)
				prev->next = current->next;
			else
				vfx->particles = current->next;
			free(current);
			if (prev)
				current = prev->next;
			else
				current = vfx->particles;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static void safe_put_pixel(int x, int y, t_img *img, int color, int alpha)
{
	int offset;
	unsigned int current_color;
	int r, g, b;
	int new_r, new_g, new_b;
	int alpha_inv;

	offset = (y * img->size_line) + (x * (img->bit_per_pixel / 8));
	current_color = *(unsigned int *)(img->img_pex_ptr + offset);
	
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	
	alpha_inv = 255 - alpha;
	new_r = ((current_color >> 16) & 0xFF) * alpha_inv / 255 + r * alpha / 255;
	new_g = ((current_color >> 8) & 0xFF) * alpha_inv / 255 + g * alpha / 255;
	new_b = (current_color & 0xFF) * alpha_inv / 255 + b * alpha / 255;
	
	new_r = (new_r > 255) ? 255 : new_r;
	new_g = (new_g > 255) ? 255 : new_g;
	new_b = (new_b > 255) ? 255 : new_b;
	
	*(unsigned int *)(img->img_pex_ptr + offset) = (new_r << 16) | (new_g << 8) | new_b;
}

void render_particles(t_visual_effects *vfx, t_img *img)
{
	t_particle *current;
	int alpha;
	int px, py;
	int size;
	int dy, dx;

	current = vfx->particles;
	while (current)
	{
		alpha = (int)(255.0 * current->lifetime / current->max_lifetime);
		px = (int)current->x;
		py = (int)current->y;
		size = current->size;
		
		/* Draw particle as small square */
		dy = -size;
		while (dy <= size)
		{
			dx = -size;
			while (dx <= size)
			{
				safe_put_pixel(px + dx, py + dy, img, current->color, alpha);
				dx++;
			}
			dy++;
		}
		
		current = current->next;
	}
}

void add_light_source(t_visual_effects *vfx, double x, double y, int intensity, int color)
{
	t_light_source *new_light;

	new_light = (t_light_source *)malloc(sizeof(t_light_source));
	if (!new_light)
		return ;
	
	new_light->x = x;
	new_light->y = y;
	new_light->intensity = intensity;
	new_light->color = color;
	new_light->radius = 100.0f;
	new_light->pulsing = 0;
	new_light->pulse_speed = 1;
	new_light->next = vfx->lights;
	vfx->lights = new_light;
}

void update_lights(t_visual_effects *vfx)
{
	t_light_source *current;
	t_light_source *prev;

	prev = NULL;
	current = vfx->lights;
	
	while (current)
	{
		if (current->pulsing)
			current->intensity -= current->pulse_speed;
		
		if (current->intensity <= 0)
		{
			if (prev)
				prev->next = current->next;
			else
				vfx->lights = current->next;
			free(current);
			if (prev)
				current = prev->next;
			else
				current = vfx->lights;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static float distance(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return (float)sqrt(dx * dx + dy * dy);
}

void render_dynamic_lighting(t_visual_effects *vfx, t_img *img)
{
	t_light_source *light;
	int px, py;
	float dist;
	float intensity_factor;
	int alpha;
	int r, g, b;
	int i, j;

	light = vfx->lights;
	while (light)
	{
		px = (int)light->x;
		py = (int)light->y;
		
		/* Draw glow circle around light */
		i = -80;
		while (i <= 80)
		{
			j = -80;
			while (j <= 80)
			{
				dist = distance(light->x, light->y, px + j, py + i);
				if (dist < light->radius)
				{
					intensity_factor = 1.0f - (dist / light->radius);
					alpha = (int)(50.0f * light->intensity / 100.0f * intensity_factor);
					
					r = (light->color >> 16) & 0xFF;
					g = (light->color >> 8) & 0xFF;
					b = light->color & 0xFF;
					
					safe_put_pixel(px + j, py + i, img, 
						(r << 16) | (g << 8) | b, alpha);
				}
				j++;
			}
			i++;
		}
		
		light = light->next;
	}
}

void cleanup_visual_effects(t_visual_effects *vfx)
{
	t_particle *current_p;
	t_particle *next_p;
	t_light_source *current_l;
	t_light_source *next_l;

	current_p = vfx->particles;
	while (current_p)
	{
		next_p = current_p->next;
		free(current_p);
		current_p = next_p;
	}
	vfx->particles = NULL;

	current_l = vfx->lights;
	while (current_l)
	{
		next_l = current_l->next;
		free(current_l);
		current_l = next_l;
	}
	vfx->lights = NULL;
}
