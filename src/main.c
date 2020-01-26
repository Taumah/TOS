#include "../headers/functions.h"
#include "../headers/commons.h"

int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("ppm.ppm");

    pixel_t test = {20, 30 ,40};
    pixel_t test2;

    printf("%lu   %lu\n" , picture.width , picture.height);

    test2 = pixel_invert(&test);


    pixel_print(&test2);

    return 0;


}