#include "functions.h"


int main(/*int argc, char** argv*/){
    
    pixel_t test = {20,20,20};

    // FILE* pix_map_file = fopen("file.ppm" , "rb");


    img_blue(&test);
    printf("\nhello world\n");

    return 0;
}