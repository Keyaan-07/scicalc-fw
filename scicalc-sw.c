#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico-displayDrivs/st7789/st7789.h"
#include "pico-displayDrivs/gfx/gfx.h"
#include "mathfuncs/mathfuncs.h"
#include "keymap.h"

#define PIN_MOSI 1
#define PIN_MISO 2
#define PIN_CS 3
#define PIN_SCLK 4

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320
// i will be using pico-displayDrivs library to drive the screen. 
uint16_t framebuf[DISPLAY_HEIGHT][DISPLAY_WIDTH];
uint8_t row_pins[5] = {4,3,2,1,0};
uint8_t col_pins[10] = {5,6,7,8,9,10,11,12,13,14};

char equation[64] = "";
int brightness = 50;
char answer[10];

int lcd_init(){
    LCD_initDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    LCD_setRotation(1);
    GFX_createFramebuf();
    GFX_clearScreen();
    GFX_flush();
    return 0;
}

void keys_matrix_init(){
    for(int i = 0; i<5; i++){
        gpio_init(i);
        gpio_set_dir(i, 1); // rows are outputs
        gpio_put(i, 0);
    }
    for(int i = 5; i<15; i++){
        gpio_init(i);
        gpio_set_dir(i, 0);  // cols are inputs
        gpio_pull_down(i);
    }
}
//replace all the printf statements with proper LCD prints later on. 
void scan_keys_matrix(){
    for(int i = 0; i<5; i++){
        gpio_put(i, 1);
        for(int j = 5; j<15;j++){
            int x = gpio_get(j);
            if(x){
                sleep_ms(5);
                int x2 = gpio_get(j);
                if(x==x2){
                    char *key_pressed = matrix[j-5][i];
                    if(key_pressed== "AC"){
                        equation[0] = '\0';
                    }
                    if(key_pressed == "DEL"){
                        int eqlen = strlen(equation);
                        equation[eqlen] = '\0'
                    }
                    if(key_pressed == "=" || key_pressed == "EXE"){
                        printf("Answer: %f", answer);
                    }

                } 
                while(gpio_get(j));
            }
        }
        gpio_put(i, 0);
    }
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

    keys_matrix_init();
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
