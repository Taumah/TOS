#include "../headers/functions.h"
#include "../headers/commons.h"

int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("small.ppm");
    ppm_image_t copy = ppm_revert(&picture);
    // pixel_t test = {20, 30 ,40};

    ppm_print(&picture);

    printf("\n\n\n\n");

    ppm_print(&copy);
    ppm_free(&picture);
    return 0;


}