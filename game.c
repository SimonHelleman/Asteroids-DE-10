#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "address_map_arm.h"
#include "de1_io.h"
#include "vga_graphics.h"
#include "vector.h"
#include "game_math.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"

// todo
// button_pressed function

#define MAX_BULLETS 5
#define MAX_ASTEROIDS 100

bool is_off_screen(const Vector2 *pos)
{
	return pos->x > VGA_PIXEL_WIDTH || pos->y > VGA_PIXEL_HEIGHT || pos->x < 0 || pos->y < 0;
}

bool rectangle_overlap_test(const Vector2 *a, uint32_t width_a, uint32_t height_a, const Vector2 *b, const uint32_t width_b, const uint32_t height_b)
{
	return a->x < b->x + width_b && 
	a->x + width_a > b->x &&
	a->y < b->y + height_b &&
	height_a + a->y > b->y;
}

void test_clear()
{
	memset((void *)FPGA_PIXEL_BUF_BASE, 0, 320 * 240 * 2);
}

int main(void)
{
	Vector2 ship_init_pos = { 30.0f, 30.0f };
	Vector2 ship_init_vel = { 0.0f, 0.0f };

	Ship ship = {ship_init_pos, ship_init_vel, 0.0f, 0.0f};

	
	Vector2 o = {0.0f, 0.0f};
	
	int num_bullets_alive = 0;
	Bullet *bullets[MAX_BULLETS];


	int num_asteroids_alive = 5;
	Asteroid asteroids[MAX_ASTEROIDS];


	Vector2 asteroid_pos_upper_limit = { VGA_PIXEL_WIDTH - ASTEROID_WIDTH, VGA_PIXEL_HEIGHT - ASTEROID_HEIGHT };
	Vector2 asteroid_pos_lower_limit = { 30.0f, 30.0f };
	
	for (int i = 0; i < num_asteroids_alive; ++i)
	{
		asteroids[i].pos.x = (float)rand() / (RAND_MAX / (asteroid_pos_upper_limit.x - asteroid_pos_lower_limit.x));
		asteroids[i].pos.y = (float)rand() / (RAND_MAX / (asteroid_pos_upper_limit.y - asteroid_pos_lower_limit.y));

		asteroids[i].vel.x = (float)rand() / (RAND_MAX / 0.1f);
		asteroids[i].vel.y = (float)rand() / (RAND_MAX / 0.1f);
	}

	vga_clear(0x0000);
	
	while (1)
	{
		// Clearing the screen is too costly atm
		// double buffering could help but I am out of time
		// to debug the memory corruption I seem to be having
		// (due to the fact that the buffer can't go in standard RAM
		// making managing the memory for this is 100% manual)
		ship_draw(&ship, VGA_COLOR_BLACK);
		
		if (read_push_btn(0))
		{
			ship.theta += RADIANS(0.1);
		}

		if (read_push_btn(1))
		{
			ship.theta -= RADIANS(0.1);
		}

		ship_update(&ship);

		ship_draw(&ship, VGA_COLOR_GREEN);

		if (read_push_btn(2))
		{
			ship.accel_mag = 0.001f;
		}
		else
		{
			ship.accel_mag = 0.0f;
		}


		if (read_switch(0))
		{
			ship.vel.x = 0.0f;
			ship.vel.y = 0.0f;
		}


		if (read_push_btn_pressed(3))
		{
			if (num_bullets_alive < MAX_BULLETS)
			{
				bullets[num_bullets_alive] = (Bullet *)malloc(sizeof(Bullet));
				Vector2 pos = { ship.pos.x, ship.pos.y };
				Vector2 vel = { taylor_sin(ship.theta), -taylor_cos(ship.theta) };
				bullets[num_bullets_alive]->pos = pos;
				bullets[num_bullets_alive]->vel = vel;
				++num_bullets_alive;
			}

		}

		for (int i = 0; i < num_bullets_alive; ++i)
		{
			bullet_draw(bullets[i], VGA_COLOR_BLACK);
			bullet_update(bullets[i]);
			bullet_draw(bullets[i], VGA_COLOR_WHITE);

			if (is_off_screen(&bullets[i]->pos))
			{
				--num_bullets_alive;
				bullet_draw(bullets[i], VGA_COLOR_BLACK);
				free(bullets[num_bullets_alive]);
				
			}
		}

		display_hex_digit(0, num_bullets_alive);


		for (int i = 0; i < num_asteroids_alive; ++i)
		{
			asteroid_draw(&asteroids[i], VGA_COLOR_BLACK);
			asteroid_update(&asteroids[i]);

			for (int j = 0; j < num_asteroids_alive; ++j)  
			{
				if (rectangle_overlap_test(&asteroids[i].pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, &asteroids[j].pos, ASTEROID_HEIGHT, ASTEROID_HEIGHT))
				{
					vector2_scale(&asteroids[i].vel, &asteroids[i].vel, -1.0f);
					vector2_scale(&asteroids[j].vel, &asteroids[j].vel, -1.0f);
				}
			}

			asteroid_draw(&asteroids[i], VGA_COLOR_RED);
		}

		vga_draw_rect(&o, 319, 239, 0xffff);        
	}
	return 0;
}