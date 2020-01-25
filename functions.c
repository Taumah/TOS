#include "functions.h"

__uint8_t img_blue(const pixel_t *p){
    
    __uint8_t test =0;

    printf("%hhu %hhu %hhu" , p->blue , p->green , p->red);
    return test;
}