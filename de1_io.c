#include <string.h>
#include "de1_io.h"
#include "address_map_arm.h"

void set_led(uint8_t n, bool val)
{
	if (n > 9) return;
	
	volatile uint32_t *led_bp = (uint32_t *)LED_BASE;		
	*led_bp = val ? *led_bp | 1 << n : *led_bp & ~(1 << n);
}

bool read_switch(uint8_t n)
{
	if (n > 9) return LOW;
	
	volatile uint32_t *sw_bp = (uint32_t *)SW_BASE;
	return *sw_bp & (1 << n);
}

uint16_t read_switch_val_unsigned()
{
	volatile uint32_t *sw_bp = (uint32_t *)SW_BASE;
	return (uint16_t)*sw_bp;
}

// Don't know when of if this is useful
// but I was board and lost in an ECE 3380 lecture
// so I did this to pass time
int16_t read_switch_val_signed()
{
	volatile uint32_t *sw_bp = (uint32_t *)SW_BASE;

	// cast to 16 bits (no data is lost)
	int16_t sw_val = (int16_t)*sw_bp;
	
	// 0x200 = 512 which is the number of values of 10 bits.
	// and this with the switch value checks if the 10th bit is set
	// if it is set the most significant bits to 1
	// otherwise set to 0
	int16_t ret = (sw_val & 0x200) ? 0xfc00 : 0x0;
	
	// 0x3ff = 1023 = 1111111111 (10 0x1)
	// and with switch value to get bits set
	// or it with above
	ret |= sw_val & 0x3ff;
	
	return ret;
}

bool read_push_btn(uint8_t n)
{
	if (n > 3) return LOW;
	volatile uint32_t *btn_bp = (uint32_t *)KEY_BASE;
	return *btn_bp & (1 << n);
}

uint8_t read_push_btn_val_unsigned()
{
	volatile uint32_t *pb_bp = (uint32_t *)KEY_BASE;
	return (uint8_t)*pb_bp;
}

void set_segment(uint8_t n, bool val)
{
	if (n > 41) return;
	volatile uint32_t *seg_bp = (uint32_t *)HEX3_HEX0_BASE;
	
	if (n > 27)
	{
		seg_bp += 4;
		n -= 28;
	}
	
	if (val)
	{
		*seg_bp |= 1 << (n + (n / 7));
	}
	else
	{
		*seg_bp &= ~(1 << (n + (n / 7)));
	}
}

void display_hex_digit(uint8_t display, int8_t digit)
{
	if (display > 5 || digit > 0xf) return;
	
	volatile uint32_t *ptr = (uint32_t *)(display >= 4 ? HEX5_HEX4_BASE : HEX3_HEX0_BASE);
	
	// memcpy doesn't like volatile pointers so we will copy the register to a variable
	const uint32_t current_value = *ptr;
	uint8_t arr[4];
	
	memcpy(arr, &current_value, 4);
	
	display = display >= 4 ? display - 4 : display; 

	const uint8_t digit_bit_patterns[] = {
		0b00111111, 0b00000110, 0b01011011, 0b01001111,
		0b01100110, 0b01101101, 0b01111101, 0b00000111,
		0b01111111, 0b01101111, 0b01110111, 0b01111100,
		0b00111001, 0b01011110, 0b01111001, 0b01110001	
	};
	
	arr[display] = digit < 0 ? 0x0 : digit_bit_patterns[digit];
	
	uint32_t val;
	memcpy(&val, arr, 4);
	
	*ptr = val;
}

void vga_draw_pixel(uint32_t x, uint32_t y, uint16_t color)
{
	if (x > 319 || y > 239) return;

	volatile uint32_t *buffer_reg = (uint32_t *)PIXEL_BUF_CTRL_BASE;

	volatile uint16_t *pixel = (uint16_t *)(*buffer_reg + (y << 10) + (x << 1));

	
	
	*pixel = color;
}

void vga_set_back_buffer(uint32_t addr)
{
	volatile uint32_t *back_buf = (uint32_t *)0xFF203024;

	*back_buf = addr;
}

void vga_swap_buffers()
{
	volatile uint32_t *buffer_reg = (uint32_t *)PIXEL_BUF_CTRL_BASE;

	*buffer_reg = 1;
}

void vga_clear(uint16_t color)
{
	for (int y = 0; y < VGA_PIXEL_HEIGHT; ++y)
	{
		for (int x = 0; x < VGA_PIXEL_WIDTH; ++x)
		{
			vga_draw_pixel(x, y, color);
		}
	}
}

void crude_delay()
{
	for (volatile int delay_cnt = 70000000; delay_cnt != 0; --delay_cnt);
}

void private_timer_enable(PrivateTimer *timer, bool status)
{
	if (status)
	{
		timer->control |= 0b001;
	}
	else
	{
		timer->control &= 0xfffffffe;
	}
}

void private_timer_continue(PrivateTimer *timer, bool status)
{
	if (status)
	{
		timer->control |= 0b010;
	}
	else
	{
		timer->control &= 0xfffffffd;
	}
}

void private_timer_enable_interrupts(PrivateTimer *timer, bool status)
{
	if (status)
	{
		timer->control |= 0b100;
	}
	else
	{
		timer->control &= 0xfffffffb;
	}
}

void private_timer_set_prescaler(PrivateTimer *timer, uint8_t prescaler)
{
	// Clear the prescaler bits
	timer->control &= 0xffff00ff;
	
	// Set prescaler
	timer->control |= (prescaler << 8);
}

void gpio_set_direction(GPIOPort *port, uint8_t pin, uint8_t direction)
{
	if (pin > 31) return;
	port->data_direction = direction ? port->data_direction | 1 << pin : port->data_direction & ~(1 << pin);
}

void gpio_write(GPIOPort *port, uint8_t pin, bool val)
{
	if (pin > 31) return;
	port->data = val ? port->data | 1 << pin : port->data & ~(1 << pin);
}

bool gpio_read(const GPIOPort *port, uint8_t pin)
{
	if (pin > 31) return false;
	return port->data & (1 << pin);
}

void adc_enable_auto_update(bool status)
{
	volatile uint32_t *ptr = (uint32_t *)(ADC_BASE + 4);
	
	// I have no idea if writing 0 to this will disable it
	// since all documentation I have just references enableing it.
	*ptr = status;
}

uint16_t adc_update_and_read(uint8_t channel)
{
	if (channel > 7) return;

	volatile uint32_t *ptr = (uint32_t *)ADC_BASE;

	// cause an update
	ptr[0] = 1;

	// wait for the ready flag
	while (!(ptr[channel] & 1 << 15)) {}

	// isolate first 12 bits
	return ptr[channel] & 0b11111111111;
}