#define POS_DIMENSIONS 3 //magicnumber + whitespace =3
#define QTY_OF_WHITESPACES 4 //according to documentation 
//http://netpbm.sourceforge.net/doc/ppm.html

#include "../headers/functions.h"
#include "../headers/commons.h"

pixel_t pixel_new(__uint8_t red, __uint8_t green, __uint8_t blue){
    pixel_t new_pixel = {0,0,0}; // initialised off (~=~ black color)
    

    new_pixel.red = red;
    new_pixel.green = green;
    new_pixel.blue = blue;
    
    return new_pixel;
}
//~~~~~~~~Structs printers~~~~~~~~~~~~~
    void pixel_print(const pixel_t* p){
        printf("%hhu  %hhu  %hhu " , p->red , p->green , p->blue);
    }

    void ppm_print(const ppm_image_t  *pic){

        for(size_t i =0 ; i < pic->height ; i++){
            for(size_t j =0 ; j < pic->width ; j++){
                pixel_print(&pic->pixel[i][j]);
                printf("\t");
            }
            printf("\n");
        }
    }
//

//~~~~~~~~PIXEL getters~~~~~~~~~~~~~~~~
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
    char* config = malloc(50*sizeof(char));
    ppm_get_config(pf_picture , config);

    //~~~~~~~Filling fields~~~~
        pic_registered.height = get_ppm_height(config);
        pic_registered.width  = get_ppm_width(config);
        pic_registered.start_pos = get_ppm_start(config);

        pic_registered.length = get_ppm_size(pf_picture);
    //

    pic_registered.pixel = (pixel_t**)malloc(pic_registered.height);

    for(__uint8_t i = 0 ; i < pic_registered.height ; i++){
        pic_registered.pixel[i] = (pixel_t*)malloc(pic_registered.width);
        
        for(__uint8_t j = 0 ; j < pic_registered.width ; j++){
            pic_registered.pixel[i][j].red = 0;
            pic_registered.pixel[i][j].green = 0; 
            pic_registered.pixel[i][j].blue = 0;
        }
    }

    // get_ppm_pixelArray(&pic_registered , pf_picture );

    fclose(pf_picture);
    free(config);

    return pic_registered;

}

//~~~~~FILE getters~~~~~~~~~
    void ppm_get_config(FILE* image_file , char* config){

        fread(config , sizeof(*config) , 20  , image_file);
        fseek(image_file , 0 , SEEK_SET); // reset cursor for further uses

    }

    size_t get_ppm_size(FILE* image_file){
        fseek(image_file , 0 , SEEK_END);

        size_t size = ftell(image_file);

        fseek(image_file , 0 , SEEK_SET);

        return size;

    }

    size_t get_ppm_height(const char* config){
        char* file_height;
        size_t height = 0;
        __uint8_t height_range = 0;
        char* start = strpbrk(config+ POS_DIMENSIONS , "\t\n\v\f\r ")+1;

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

    __uint8_t get_ppm_start(const char* config){
        __int8_t counter = 0;
        __int8_t i;
        for(i = 0 ; i < (__int8_t)strlen(config) ; counter += !is_whitespace(config[i]) , i++){
            if(counter == QTY_OF_WHITESPACES){  
                return i;
            }
        }
        // means we can't find file start
        return 0; 
    }

    void get_ppm_pixelArray(const ppm_image_t* pic , FILE* pfile ){
        if( !pic->height || !pic->width || !pic->length){
            printf("field missing");
            exit(1);
        }

        fseek(pfile , pic->start_pos * sizeof(__uint8_t) , SEEK_SET);
        size_t i , j;
        for(i = 0 ; i < pic->height ; i++){
            for (j = 0; i < pic->width; j++){
                pic->pixel[i][j] = pixel_new(0,0,0);
                pixel_print(&pic->pixel[i][j]);   
            }
            
        }


    }
//

bool pixel_equals(const pixel_t* self, const pixel_t* other){
    bool valid = pixel_green(self) == pixel_green(other);
    valid &= pixel_red(self) ==  pixel_red(other);
    valid &= pixel_blue(self) ==  pixel_blue(other);

    return valid;
}

pixel_t pixel_invert(const pixel_t* pix){
    pixel_t copy;

    copy.red    =  ~pixel_red(pix);
    copy.green  =  ~pixel_green(pix);
    copy.blue   =  ~pixel_blue(pix);

    return copy;
}

void ppm_free(ppm_image_t* picture){
    
    for(long i = (long)picture->height-1 ; i >= 0 ; i--){
        printf("%lu \n %hhu %hhu %hhu \n" ,i, picture->pixel[i]->red , picture->pixel[i]->green , picture->pixel[i]->blue );
        free(picture->pixel[i]);
/*         printf("%lu" , i);
 */    }

    free(picture->pixel);
}