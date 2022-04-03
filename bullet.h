#ifndef BULLET_H
#define BULLET_H
#include <stdint.h>
#include "vector.h"

typedef struct
{
    Vector2 pos;
    Vector2 vel;
} Bullet;

void bullet_draw(const Bullet *bullet, uint16_t color);
void bullet_update(Bullet *bullet);




#endif