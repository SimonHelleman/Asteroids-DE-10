#include "asteroid.h"
#include "de1_io.h"
#include "vga_graphics.h"

void asteroid_draw(const Asteroid *asteroid, uint16_t color)
{
	vga_draw_rect(&asteroid->pos, ASTEROID_WIDTH, ASTEROID_HEIGHT, color);
}


void asteroid_update(Asteroid *asteroid)
{
	vector2_add(&asteroid->pos, &asteroid->pos, &asteroid->vel);

	if (asteroid->pos.x + ASTEROID_WIDTH > VGA_PIXEL_WIDTH)
	{
		asteroid->pos.x = 0.0f;
	}

	if (asteroid->pos.y + ASTEROID_HEIGHT > VGA_PIXEL_HEIGHT)
	{
		asteroid->pos.y = 0.0f;
	}

	if (asteroid->pos.x < 0)
	{
		asteroid->pos.x = VGA_PIXEL_WIDTH - ASTEROID_WIDTH - 1;
	}

	if (asteroid->pos.y < 0)
	{
		asteroid->pos.y = VGA_PIXEL_HEIGHT - ASTEROID_HEIGHT - 1;
	}
}