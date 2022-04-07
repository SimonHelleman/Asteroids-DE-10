#ifndef DE1_IO_H
#define DE1_IO_H
#include <stdint.h>
#include <stdbool.h>

#define HIGH				0x1
#define LOW					0x0

#define OUTPUT				0x1
#define INPUT				0x0

#define VGA_PIXEL_WIDTH		320
#define VGA_PIXEL_HEIGHT	240
#define VGA_COLOR_WHITE		0xffff
#define VGA_COLOR_RED		0xf800
#define VGA_COLOR_GREEN		0x07e0
#define VGA_COLOR_BLUE		0x001f
#define VGA_COLOR_BLACK		0x0000

// Maybe sometime I will get around
// to writing some functions to interface with this
typedef struct
{
	uint32_t status;
	uint32_t control;
	uint32_t low_period;
	uint32_t high_period;
	uint32_t low_counter;
	uint32_t high_counter;
} IntervalTimer;

// Again, havent used this yet. Maybe some day
typedef struct
{
	uint32_t load;
	uint32_t count;
	uint32_t control;
	uint32_t end_of_interrupt;
	uint32_t interrupt;
} HPSTimer;


// Don't need this since both timers are mapped to the same memory address
typedef struct
{
	uint32_t load;
	uint32_t count;
	uint32_t control;
	uint32_t status;
} PrivateTimer;

// There are more registers than these, but I don't really
// care at this point to included them
typedef struct
{
	uint32_t data;
	uint32_t data_direction;
} GPIOPort;

void set_led(uint8_t n, bool val);
bool read_switch(uint8_t n);
uint16_t read_switch_val_unsigned();
int16_t read_switch_val_signed();
bool read_push_btn(uint8_t n);
bool read_push_btn_pressed(uint8_t n); // Only high on transition
uint8_t read_push_btn_val_unsigned();
void set_segment(uint8_t n, bool val);
void display_hex_digit(uint8_t display, int8_t digit);
void vga_draw_pixel(uint32_t x, uint32_t y, uint16_t color);
void vga_set_back_buffer(uint32_t addr);
void vga_swap_buffers();
void vga_clear(uint16_t color);
void crude_delay();
void private_timer_enable(PrivateTimer *timer, bool status);
void private_timer_continue(PrivateTimer *timer, bool status);
void private_timer_enable_interrupts(PrivateTimer *timer, bool status);
void private_timer_set_prescaler(PrivateTimer *timer, uint8_t prescaler);
void gpio_set_direction(GPIOPort *port, uint8_t pin, uint8_t mode);
void gpio_write(GPIOPort *port, uint8_t pin, bool val);
bool gpio_read(const GPIOPort *port, uint8_t pin);
void adc_enable_auto_update(bool status);
uint16_t adc_update_and_read(uint8_t channel);
#endif