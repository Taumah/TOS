#include "functions.h"


int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("ppm.ppm");

    printf("%lu   %lu\n" , picture.width , picture.height);

    return 0;
}