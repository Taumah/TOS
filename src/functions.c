#define POS_DIMENSIONS 3 //magicnumber + whitespace =3

#include "../headers/functions.h"

pixel_t pixel_new(__uint8_t red, __uint8_t green, __uint8_t blue){
    
    pixel_t new_pixel = {0,0,0}; // initialised off (~=~black color)

    new_pixel.red = red;
    new_pixel.green = green;
    new_pixel.blue = blue;
    
    return new_pixel;
}

//~~~~~~~~PIXEL getters~~~~~~~~~~
    __uint8_t pixel_red(const pixel_t *p){
        return p->red;
    }
    __uint8_t pixel_green(const pixel_t *p){
        return p->green;
    }
    __uint8_t pixel_blue(const pixel_t *p){
        return p->blue;
    }
//

ppm_image_t ppm_new(const char *pathname){
    ppm_image_t pic_registered;

    FILE* pf_picture = fopen(pathname , "rb");
    char* config = malloc(40*sizeof(char));

    ppm_get_config(pf_picture , config);

    //~~~~~~~Filling fields~~~~
        pic_registered.height = get_ppm_height(config);
        pic_registered.width  = get_ppm_width(config);

        pic_registered.length = get_ppm_size(pf_picture);
    //

    fclose(pf_picture);
    free(config);
    return pic_registered;

}

//~~~~~FILE getters~~~~~~~~~
    void ppm_get_config(FILE* image_file , char* config){

        fread(config , sizeof(__uint8_t) , 40*sizeof(__uint8_t) , image_file);
        fseek(image_file , 0 , SEEK_SET); // reset cursor for further uses

    }

    size_t get_ppm_size(FILE* image_file){
        fseek(image_file , 0 , SEEK_END);

        __uint16_t size = ftell(image_file);

        fseek(image_file , 0 , SEEK_SET);

        return size;

    }

    size_t get_ppm_height(const char* config){
        char* file_height;
        size_t height = 0;
        __uint8_t height_range = 0;
        char* start = strpbrk(config , "\t\n\v\f\r ")+1;

        while(is_whitespace(start[height_range] )|| height_range > 12 )
            height_range++;

        
        file_height = malloc(height_range);
        strncpy(file_height , start , height_range);
        height = atoi(file_height);

        printf("largeur %hhu , valeur %lu \n" , height_range , height);

        free(file_height);

        return height;
    }

    size_t get_ppm_width(const char* config){
        char* file_width;
        size_t width = 0;
        __uint8_t width_range = 0;

        while(strchr("\t\n\v\f\r ", config[POS_DIMENSIONS + width_range]) == NULL || width_range > 12) // 2nd condition to avoid infinite loops
            width_range++;


        file_width = malloc(width_range * sizeof(char));
        if(file_width != NULL){
            strncpy(file_width , (config + POS_DIMENSIONS), width_range);
            width = atoi(file_width);

            printf("longueur %hhu ,valeur %lu \n" , width_range , width);

            free(file_width);
            return width;
        }
        else{
            printf("Erreur lors du calcul des dimensions de l'image");
            return EXIT_FAILURE;
        }
        
    }
//

