#include "../headers/functions.h"
#include "../headers/commons.h"

int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("small.ppm");

    // pixel_t test = {20, 30 ,40};

    ppm_free(&picture);
    return 0;


}