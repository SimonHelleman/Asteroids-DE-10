#include <stdlib.h>
#include "game_math.h"
#include "de1_io.h"
#include "vga_graphics.h"

static void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void vga_draw_line(const Vector2 *a, const Vector2 *b, uint16_t color)
{
    int x1 = round_to_int(a->x);
    int y1 = round_to_int(a->y);
    int x2 = round_to_int(b->x);
    int y2 = round_to_int(b->y);

    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;

    if (dx == 0) // Line is vertical
    {
        if (y2 < y1)
            swap_int(&y1, &y2);
        for (y = y1; y <= y2; y++)
            vga_draw_pixel(x1, y, color);
        return;
    }

    if (dy == 0) // Line is horizontal
    {
        if (x2 < x1)
            swap_int(&x1, &x2);
        for (x = x1; x <= x2; x++)
            vga_draw_pixel(x, y1, color);
        return;
    }

    // Line is Funk-aye
    dx1 = abs(dx);
    dy1 = abs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        vga_draw_pixel(x, y, color);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
                px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y = y + 1;
                else
                    y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            vga_draw_pixel(x, y, color);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        vga_draw_pixel(x, y, color);

        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x = x + 1;
                else
                    x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            
            vga_draw_pixel(x, y, color);
        }
    }
}

void vga_draw_rect(const Vector2 *pos, uint32_t w, uint32_t h, uint16_t color)
{
    //    a(x, y)        b(x + w, y)
    //    -------------------
    //    |                 |
    //    |                 |
    //    -------------------
    //    d(x, y + h)    c(x + w, y + h)

    Vector2 b = {pos->x + w, pos->y};
    Vector2 c = {pos->x + w, pos->y + h};
    Vector2 d = {pos->x, pos->y + h};

    vga_draw_line(pos, &b, color);
    vga_draw_line(&b, &c, color);
    vga_draw_line(&d, &c, color);
    vga_draw_line(pos, &d, color);
}

void vga_fill_rect(const Vector2 *pos, uint32_t w, uint32_t h, uint16_t color)
{
    int x = round_to_int(pos->x);
    int y = round_to_int(pos->y);

    for (int i = x; i < x + w; ++i)
    {
        for (int j = y; j < y + h; ++j)
        {
            vga_draw_pixel(x, y, color);
        }
    }
}

void vga_draw_circle(const Vector2 *pos, uint32_t r, uint16_t color)
{
}

void vga_fill_circle(const Vector2 *pos, uint32_t r, uint16_t color)
{
}

void vga_draw_triangle(const Vector2 *a, const Vector2 *b, const Vector2 *c, uint16_t color)
{
    vga_draw_line(a, b, color);
    vga_draw_line(b, c, color);
    vga_draw_line(c, a, color);
}

void vga_fill_triangle(const Vector2 *a, const Vector2 *b, const Vector2 *c, uint16_t color)
{
}