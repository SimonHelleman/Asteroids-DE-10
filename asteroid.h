#include <stdint.h>
#include "vector.h"

#define ASTEROID_WIDTH  30
#define ASTEROID_HEIGHT 30

typedef struct
{
    Vector2 pos;
    Vector2 vel;
} Asteroid;

void asteroid_draw(const Asteroid *asteroid, uint16_t color);
void asteroid_update(Asteroid *asteroid);