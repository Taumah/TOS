#include "../headers/functions.h"
#include "../headers/commons.h"

int main(/*int argc, char** argv*/){
    
    ppm_image_t picture = ppm_new("small.ppm");

    // pixel_t test = {20, 30 ,40};

    // printf("\n\n\n\n\n");
    // ppm_print(&picture);
    // printf("\n\n\n\n\n");
    char text[100];

    FILE* pf = fopen("small.ppm" , "rb");

    fread(text , sizeof(char) , 90 , pf );

    printf("%s" , text);

    ppm_free(&picture);
    return 0;


}