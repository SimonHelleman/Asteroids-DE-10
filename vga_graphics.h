#ifndef VGA_GRAPHICS_H
#define VGA_GRAPHICS_H
#include <stdint.h>

#include "vector.h"

void vga_draw_line(const Vector2 *a, const Vector2 *b, uint16_t color);

void vga_draw_rect(const Vector2 *pos, uint32_t w, uint32_t h, uint16_t color);
void vga_fill_rect(const Vector2 *pos, uint32_t w, uint32_t h, uint16_t color);

void vga_draw_circle(const Vector2 *pos, uint32_t r, uint16_t color);
void vga_fill_circle(const Vector2 *pos, uint32_t r, uint16_t color);

void vga_draw_triangle(const Vector2 *a, const Vector2 *b, const Vector2 *c, uint16_t color);
void vga_fill_triangle(const Vector2 *a, const Vector2 *b, const Vector2 *c, uint16_t color);

#endif