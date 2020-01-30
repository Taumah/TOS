#include "../headers/functions.h"
#include "../headers/commons.h"

int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("small.ppm");
    ppm_image_t copy = ppm_revert(&picture);
    // pixel_t test = {20, 30 ,40};

    ppm_print(&copy);

    ppm_file_from_pic(&picture , "picture.ppm");
    ppm_file_from_pic(&copy , "copy.ppm");

    printf("il y a %lu pixel(s) noirs \n\n\n\n" , ppm_black_counter(&copy));

    ppm_free(&picture);
    ppm_free(&copy);

    return 0;


}