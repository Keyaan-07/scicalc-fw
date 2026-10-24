#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico-displayDrivs/st7789/st7789.h"
#include "pico-displayDrivs/gfx/gfx.h"
#include "mathfuncs/mathfuncs.h"

#define PIN_MOSI 1
#define PIN_MISO 2
#define PIN_CS 3
#define PIN_SCLK 4

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320
// i will be using pico-displayDrivs library to drive the screen. 
uint16_t framebuf[DISPLAY_HEIGHT][DISPLAY_WIDTH];

void lcd_init(){
    LCD_initDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    LCD_setRotation(1);
    GFX_createFramebuf();
    GFX_clearScreen();
    GFX_flush();
}

int main()
{
    // taken from the pico-displayDrivs example: 
    int c = 0;
    stdio_init_all();
    spi_init(spi0, 1000*1000);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCLK, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_function(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    lcd_init();
    
    while (true) {
        for(int i = 0; i<DISPLAY_HEIGHT; i++){
            for(int j = 0;j<DISPLAY_WIDTH;j++){
                
            }
        }
        GFX_setCursor(0,0);
        GFX_printf("Hello, World %d", ++c);
        GFX_flush();
    }
}
