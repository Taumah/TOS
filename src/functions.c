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
        printf("%hhu %hhu %hhu \t" , p->red , p->green , p->blue);
    }

    void ppm_print(const ppm_image_t  *pic){

        for(size_t i =0 ; i < pic->height ; i++){
            for(size_t j =0 ; j < pic->width ; j++){
                pixel_print(&pic->pixel[i * pic->width + j]);
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
    char config[30] = "";
    ppm_get_config(pf_picture , config);

    //~~~~~~~Filling fields~~~~
        pic_registered.height = get_ppm_height(config);
        pic_registered.width  = get_ppm_width(config);
        pic_registered.start_pos = get_ppm_start(config);

        pic_registered.length = get_ppm_size(pf_picture);
    //

    pic_registered.pixel = (pixel_t*)malloc(pic_registered.height * pic_registered.width*sizeof(pixel_t));
    
    get_ppm_pixelArray(&pic_registered , pf_picture);
    fclose(pf_picture);
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
        char file_height[8] = "";
        size_t height = 0;
        __uint8_t height_range = 0;
        char* start = strpbrk(config+ POS_DIMENSIONS , "\t\n\v\f\r ")+1;

        while(is_whitespace(start[height_range] )|| height_range > 8 )
            height_range++;

        
        strncpy(file_height , start , height_range);
        height = atoi(file_height);

        return height;
    }

    size_t get_ppm_width(const char* config){
        char file_width[8] = "";
        size_t width = 0;
        __uint8_t width_range = 0;

        while(strchr("\t\n\v\f\r ", config[POS_DIMENSIONS + width_range]) == NULL || width_range > 12) // 2nd condition to avoid infinite loops
            width_range++;


        strncpy(file_width , (config + POS_DIMENSIONS), width_range);
        width = atoi(file_width);

        return width;
        
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
        __uint8_t constructor[3];
        if( !pic->height || !pic->width || !pic->length){
            printf("field missing");
            exit(1);
        }

        fseek(pfile , pic->start_pos * sizeof(__uint8_t) , SEEK_SET);
        size_t i , j;
        for(i = 0 ; i < pic->height ; i++){
            for (j = 0; j < pic->width; j++){

                fread(&constructor , sizeof(__uint8_t) , 3 , pfile);
                pic->pixel[i * pic->width + j ] = pixel_new(constructor[0] , constructor[1] , constructor[2]);
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

//~~~~~~REVERTERS~~~~~~~~~~~~~
    pixel_t pixel_invert(const pixel_t* pix){
        pixel_t copy;

        copy.red    =  ~pixel_red(pix);
        copy.green  =  ~pixel_green(pix);
        copy.blue   =  ~pixel_blue(pix);

        return copy;
    }
    ppm_image_t ppm_revert(const ppm_image_t* origin ){
        ppm_image_t recent;

        ppm_copy_attributes( &recent , origin);

        recent.pixel = malloc(recent.length);

        for(size_t i = 0 ; i < recent.height ; i++){
            for (size_t j = 0; j < recent.width; j++)
            {
                recent.pixel[i*recent.width + j] = pixel_invert(&origin->pixel[i*origin->width + j]);
            }
            
        }

        return recent;
    }
    
//


void ppm_free(ppm_image_t* picture){
    free(picture->pixel);
}

void ppm_copy_attributes(ppm_image_t* recent ,const ppm_image_t* origin){
    recent->height = origin->height;
    recent->width = origin->width;
    recent->length = origin->length;
    recent->start_pos = origin->start_pos;

}


void ppm_file_from_pic(const ppm_image_t* origin , const char* filepath){
    FILE* new_file = fopen(filepath , "wb");
    pixel_t pixel_tmp = {0,0,0};
    char config[30];

    sprintf(config , "P6\n%lu %lu\n255\n", origin->width , origin->height);

    fwrite(config , sizeof(char) , strlen(config) , new_file );

    for(size_t i = 0 ; i < origin->height ; i++){

        for(size_t j = 0 ; j < origin->width ; j++){
            //recuperer pixel du tableau , (3x byte) --> ecrire 3 bytes dans fichier
            pixel_tmp = ppm_get_pixel_at(origin , j , i);
            fwrite(&pixel_tmp , sizeof(__uint8_t) , 3 , new_file);
        }
    }

    fclose(new_file);
}

pixel_t ppm_get_pixel_at(const ppm_image_t *img, const size_t x, const size_t y){

    size_t i = x + y* img->width;
    pixel_print(&img->pixel[i]);

    printf("\n i vaut %p %lu\n" , &img->pixel[i] , i );
    return img->pixel[i];
}

bool is_pixel_black(const pixel_t *p){
    bool result = true;

    result &= !pixel_blue(p);
    result &= !pixel_green(p);
    result &= !pixel_red(p);

    return result;
}

size_t ppm_black_counter(const ppm_image_t *img){
    size_t counter = 0;
    for( size_t row = 0 ; row <  img->height ; row++){
        for( size_t col = 0 ; col < img->width ; col++){
            counter += is_pixel_black(&img->pixel[row* img->width + col]);
        }
    }
    return counter;
}

void ppm_black_counter_with_multithread(const ppm_image_t *img ,thread_data_t* thread_nbr){

    size_t begin = 0 , end = 0 ;

    if(thread_nbr->thread_id == 0){ 
        end = img->height*img->width/2 ;

    } 
    else{
        begin = img->height*img->width/2;
        end = img->height*img->width;
    }

    for(size_t pos = begin ; pos < end ; pos++){
        if(is_pixel_black(&img->pixel[pos])){
            shared_counter_increment(thread_nbr->shared_counter);
        }
    }
}


shared_counter_t * shared_counter_new(void) {
    shared_counter_t * sc = malloc(sizeof(shared_counter_t));
    sc->counter = 0;
    return sc;
}

void shared_counter_drop(shared_counter_t * sc) {
    free(sc);
}

void shared_counter_increment(shared_counter_t * sc) {
    sc->counter += 1;
}

int shared_counter_value(const shared_counter_t * sc) {
    return sc->counter;
}

