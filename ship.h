#ifndef SHIP_H
#define SHIP_H
#include <stdint.h>
#include "vector.h"

typedef struct
{
	Vector2 pos;
	Vector2 vel;
	Vector2 accel;
	float theta;
} Ship;

void ship_draw(const Ship *ship, uint16_t color);

void ship_update(Ship *ship);
#endif
