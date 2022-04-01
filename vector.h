#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
	float x, y;
} Vector2;

void vector2_add(Vector2 *dest, const Vector2 *a, const Vector2 *b);
void vector2_sub(Vector2 *dest, const Vector2 *a, const Vector2 *b);
void vector2_rotate(Vector2 *dest, const Vector2 *src, float theta);
float vector2_magnitude(const Vector2 *vec);
void vector2_norm(Vector2 *dest, const Vector2 *src);
void vector2_scale(Vector2 *dest, const Vector2 *src, float scale);
void vector2_translate(Vector2 *dest, const Vector2 *src, float tx, float ty);

#endif
