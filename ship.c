#include "vga_graphics.h"
#include "ship.h"
#include "de1_io.h"
#include "game_math.h"

static const Vector2 g_ship_model[] = { { 0.0f, -5.0f }, { -2.5f, 2.5f }, { 2.5f, 2.5f } };

void ship_draw(const Ship *ship, uint16_t color)
{
	Vector2 a = g_ship_model[0];
	Vector2 b = g_ship_model[1];
	Vector2 c = g_ship_model[2];

	vector2_rotate(&a, &a, ship->theta);
	vector2_rotate(&b, &b, ship->theta);
	vector2_rotate(&c, &c, ship->theta);

	vector2_scale(&a, &a, 4.0f);
	vector2_scale(&b, &b, 4.0f);
	vector2_scale(&c, &c, 4.0f);

	vector2_translate(&a, &a, ship->pos.x, ship->pos.y);
	vector2_translate(&b, &b, ship->pos.x, ship->pos.y);
	vector2_translate(&c, &c, ship->pos.x, ship->pos.y);

	vga_draw_triangle(&a, &b, &c, color);
}

void ship_update(Ship *ship)
{
	float accel_mag = vector2_magnitude(&ship->accel);

	Vector2 thrust = { taylor_sin(ship->theta) * accel_mag, -taylor_cos(ship->theta) * accel_mag };
	
	if (vector2_magnitude(&ship->vel) <= 5.0f)
	{
		vector2_add(&ship->vel, &ship->vel, &thrust);
	}
	else
	{
		if ((thrust.x >= 0 && ship->vel.x <= 0) || (thrust.x <= 0 && ship->vel.x >= 0))
		{
			ship->vel.x += thrust.x;
		}

		if ((thrust.y >= 0 && ship->vel.y <= 0) || (thrust.y <= 0 && ship->vel.y >= 0))
		{
			ship->vel.y += thrust.y;
		}
	}

	vector2_add(&ship->pos, &ship->pos, &ship->vel);
	wrap_val(&ship->pos.x, 0.0f, VGA_PIXEL_WIDTH);
	wrap_val(&ship->pos.y, 0.0f, VGA_PIXEL_HEIGHT);

	
}