#include "game_math.h"
#include "vector.h"

void vector2_add(Vector2 *dest, const Vector2 *a, const Vector2 *b)
{
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
}

void vector2_sub(Vector2 *dest, const Vector2 *a, const Vector2 *b)
{
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;	
}

void vector2_rotate(Vector2 *dest, const Vector2 *src, float theta)
{
	const float x = src->x;
	const float y = src->y;
	dest->x = x * taylor_cos(theta) - y * taylor_sin(theta);
	dest->y = y * taylor_cos(theta) + x * taylor_sin(theta);
}

float vector2_magnitude(const Vector2 *vec)
{
	return bin_search_sqrt(vec->x * vec->x + vec->y * vec->y);
}

void vector2_norm(Vector2 *dest, const Vector2 *src)
{
	float mag = vector2_magnitude(src);
	dest->x = src->x / mag;
	dest->y = src->y / mag;	
}

void vector2_scale(Vector2 *dest, const Vector2 *src, float scale)
{
	dest->x = src->x * scale;
	dest->y = src->y * scale;
}

void vector2_translate(Vector2 *dest, const Vector2 *src, float tx, float ty)
{
	dest->x = src->x + tx;
	dest->y = src->y + ty;
}