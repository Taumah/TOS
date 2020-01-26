#include "functions.h"


int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("ppm.ppm");

    printf("%lu\n" , picture.length);

    return 0;
}