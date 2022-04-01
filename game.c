#include <stdio.h>
#include "address_map_arm.h"
#include "de1_io.h"
#include "vga_graphics.h"
#include "vector.h"
#include "game_math.h"
#include "ship.h"

int main(void)
{
    Vector2 pos = {30.0f, 30.0f};
    Vector2 vel = {0.0f, 0.0f};
    Vector2 accel = {0.0f, 0.0f};

    Ship ship = {pos, vel, accel, 0.0f};

    
    Vector2 o = {0.0f, 0.0f};
    
    vga_set_back_buffer(0xC0000000);
    
    vga_clear(0x0000);
    vga_swap_buffers();
    vga_clear(0xFFFF);
    vga_swap_buffers();
    
    while (1)
    {
        crude_delay();
        vga_swap_buffers();
        crude_delay();
        vga_swap_buffers();
        /*

        //vga_clear(0x0000);
        
        ship_draw(&ship, VGA_COLOR_GREEN);

        //vga_draw_rect()

        if (read_push_btn(0))
        {
            ship_draw(&ship, VGA_COLOR_BLACK);
            //vga_swap_buffers();
            //ship_draw(&ship, VGA_COLOR_BLACK);
            //vga_swap_buffers();

            ship.theta += RADIANS(0.1);
        }

        vga_draw_rect(&o, 319, 239, 0xffff);

        //vga_swap_buffers();
        */
    }
    return 0;
}