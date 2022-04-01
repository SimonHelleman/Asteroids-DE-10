#include "vga_graphics.h"
#include "ship.h"


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