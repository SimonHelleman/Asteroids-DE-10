#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "address_map_arm.h"
#include "de1_io.h"
#include "vga_graphics.h"
#include "vector.h"
#include "game_math.h"
#include "ship.h"
#include "bullet.h"

#define MAX_BULLETS 5

bool is_off_screen(const Vector2 *pos)
{
    return pos->x > VGA_PIXEL_WIDTH || pos->y > VGA_PIXEL_HEIGHT || pos->x < 0 || pos->y < 0;
}

int main(void)
{
    Vector2 pos = {30.0f, 30.0f};
    Vector2 vel = {0.0f, 0.0f};

    Ship ship = {pos, vel, 0.0f, 0.0f};

    
    Vector2 o = {0.0f, 0.0f};
    
    int num_bullets_alive = 0;
    Bullet *bullets[MAX_BULLETS];
        
    while (1)
    {
        ship_update(&ship);

        if (read_push_btn(0))
        {
            ship_draw(&ship, VGA_COLOR_BLACK);
            //vga_swap_buffers();
            //ship_draw(&ship, VGA_COLOR_BLACK);
            //vga_swap_buffers();

            ship.theta += RADIANS(0.1);
        }

        if (read_push_btn(1))
        {
            if (num_bullets_alive < MAX_BULLETS)
            {
                bullets[num_bullets_alive] = (Bullet *)malloc(sizeof(Bullet *));
                Vector2 pos = { ship.pos.x, ship.pos.y };
                Vector2 vel = { taylor_sin(ship.theta), -taylor_cos(ship.theta) };
                bullets[num_bullets_alive]->pos = pos;
                bullets[num_bullets_alive]->vel = vel;
                ++num_bullets_alive;
            }

        }

        for (int i = 0; i < num_bullets_alive; ++i)
        {
            bullet_draw(bullets[i], VGA_COLOR_BLACK);
            bullet_update(bullets[i]);
            bullet_draw(bullets[i], VGA_COLOR_WHITE);

            if (is_off_screen(&bullets[i]->pos))
            {
                --num_bullets_alive;
                free(bullets[num_bullets_alive]);
            }
        }

        vga_draw_rect(&o, 319, 239, 0xffff);        
    }
    return 0;
}