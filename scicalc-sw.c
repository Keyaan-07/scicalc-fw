#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico-displayDrivs/st7789/st7789.h"
#include "pico-displayDrivs/gfx/gfx.h"
#include "mathfuncs/mathfuncs.h"
#include "keymap.h"
#include "hardware/pwm.h"

// map these to actual pins before compiling:
#define PIN_MOSI 1
#define PIN_MISO 2
#define PIN_CS 3
#define PIN_SCLK 4
#define BRIGHTNESS_GPIO 15 

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320
// i will be using pico-displayDrivs library to drive the screen. 
uint16_t framebuf[DISPLAY_HEIGHT][DISPLAY_WIDTH];
uint8_t row_pins[5] = {4,3,2,1,0};
uint8_t col_pins[10] = {5,6,7,8,9,10,11,12,13,14};

enum keyCodes equation[64];

int tokens = 0;
int brightness_count = 50;
char answer[10];
int cursor_pos = 0;
bool shifted = false;
bool graph_mode = false;
bool brt_mode = 0;
float ans_val = 0.0;

int lcd_init(){
    LCD_initDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    LCD_setRotation(1);
    GFX_createFramebuf();
    GFX_clearScreen();
    GFX_flush();
    return 0;
}

void updateBrightness(){
    if(brightness_count>100) brightness_count = 100;
    else if(brightness_count<0) brightness_count = 0;

    pwm_set_gpio_level(BRIGHTNESS_GPIO, brightness_count*65535/100);

}

float evaluate(char *eqn){

}

void displayGraph(){

}

void updateVars(){

}

void displayAnswer(){
    char math_str[128] = "";

    for(int i = 0; i<tokens; i++){
        if(equation[i] == ans){
            strcat(math_str, answer);
        }
        else{
            int row = equation[i]/5;
            int col = equation[i]%5;
            strcat(math_str, keymap[row][col]);
        }


        if(checkComplete(math_str)){
            ans_val = evaluate(math_str);
            GFX_printf("%.4f", ans_val);
            GFX_flush();
        }
    }
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
                    enum keyCodes token_id = ((j-5)*5) +i;
                    if(token_id == AC){
                        tokens = 0;
                        cursor_pos = 0;
                        ans_val = 0.0;
                        memset(answer, 0, sizeof(answer));
                        GFX_clearScreen();
                        GFX_flush();
                    }
                    else if(token_id == DEL){
                        if(tokens>0){
                            for(int k = cursor_pos; k>0;k--){
                                equation[k-1] = equation[k];
                            }
                            tokens--;
                            cursor_pos--;
                        }
                    }
                    else if(token_id == exe || token_id == equal){
                        displayAnswer();
                    }
                    else if(token_id == UP || token_id == DN){
                        
                    }
                    else if(token_id == RT){
                        if(brt_mode){
                            if(brightness_count<90) brightness_count += 10;
                            updateBrightness();
                        }
                        else {if(cursor_pos<tokens) cursor_pos++;}
                    }
                    else if(token_id == LT){
                        if(brt_mode){
                            if(brightness_count>10) brightness_count -= 10;
                            updateBrightness();
                        }
                        else {if(cursor_pos>0) cursor_pos--;}
                    }
                    else if(token_id == BRT){
                        if(brt_mode) brt_mode = 0;
                        else brt_mode = 1;
                    }
                    else if(token_id == grph){
                        graph_mode = 1;
                        displayGraph();
                    }
                    else if(token_id == shift){
                        shifted = 1;
                    }
                    else if(token_id == vars){
                        updateVars();
                    }
                    else{
                        equation[cursor_pos] = token_id;
                        if(cursor_pos==tokens) tokens++;
                        cursor_pos++;
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

    gpio_init(BRIGHTNESS_GPIO);
    gpio_set_function(BRIGHTNESS_GPIO, GPIO_FUNC_PWM);
    uint brt_slice = pwm_gpio_to_slice_num(BRIGHTNESS_GPIO);
    pwm_set_enabled(brt_slice, 1);
    pwm_set_wrap(brt_slice, 65535);

    keys_matrix_init();
    lcd_init();
    
    while(true){
        GFX_clearScreen();
        GFX_setCursor(0,0);

        for(int i = 0; i<=tokens; i++){
            if(i==cursor_pos){
                GFX_printf("_");
            }
            if (i<tokens){
                int row = equation[i]/5;
                int col = equation[i]%5;
                GFX_printf("%s", keymap[row][col]);
            }
        }


        if(shifted){
            GFX_setCursor(0, 300);
            GFX_printf("SHIFT");
        }
        if(brt_mode){
            GFX_setCursor(0, 200);
            GFX_printf("BRIGHTNESS: %d", brightness_count);
        }
        GFX_flush();

        scan_keys_matrix();
        
    }
}
