#include "bullet.h"
#include "vga_graphics.h"

void bullet_draw(const Bullet *bullet, uint16_t color)
{
	vga_fill_rect(&bullet->pos, BULLET_WIDTH, BULLET_HEIGHT, color);
}

void bullet_update(Bullet *bullet)
{
	vector2_add(&bullet->pos, &bullet->pos, &bullet->vel);
}
