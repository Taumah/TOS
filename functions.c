#include "functions.h"

__uint8_t img_blue(const pixel_t *p){
    
    __uint8_t test =0;

    printf("%hhu %hhu %hhu" , p->blue , p->green , p->red);
    return test;
}

pixel_t pixel_new(__uint8_t red, __uint8_t green, __uint8_t blue){
    
    pixel_t new_pixel = {0,0,0}; // initialised off (~=~black color)

    new_pixel.red = red;
    new_pixel.green = green;
    new_pixel.blue = blue;
    
    return new_pixel;
}

__uint8_t pixel_red(const pixel_t *p){
    return p->red;
}
__uint8_t pixel_green(const pixel_t *p){
    return p->green;
}
__uint8_t pixel_blue(const pixel_t *p){
    return p->blue;
}


