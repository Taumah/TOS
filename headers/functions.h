#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// #include <ctype.h>

//~~~~~~~~structures~~~~~~~~~~~~
    typedef struct pixel_t{
        //3bytes embodying each RGB byte
        __uint8_t red;
        __uint8_t green;
        __uint8_t blue;
    } pixel_t;

    typedef struct ppm_image_t{
        //squared image , so 2Dimensions needed (L*l)
        size_t height;
        size_t width;
        size_t length;

        //ppm files starts with few information bytes , which are skipped with this index        
        __uint8_t start_pos;
        
        pixel_t* pixel; // litterally 1D array of byte (used as a 2D array :*)

    }ppm_image_t;
//

//~~~~~~~~~Printers~~~~~~~~~~~
    //one line printf of `pix` fields
    void pixel_print(const pixel_t* pix);

    //prints whole pixel array from `pic`
    void ppm_print(const ppm_image_t *pic);
//

//~~~~~~~~"Hydrators"~~~~~~~~~~~

    //returns a totally field ppm_image_t from `pathname`(path to file) given
    ppm_image_t ppm_new(const char *pathname);

    //fills field "pixel" of a ppm_image_t by reading given file
    void get_ppm_pixelArray(const ppm_image_t* pic , FILE* pfile );

    // returns negative of `origin` ppm_image
    ppm_image_t ppm_revert(const ppm_image_t* origin);

    //returns a complete pixel_t struct created from 3 bytes (1/color) 
    pixel_t pixel_new(__uint8_t red, __uint8_t green, __uint8_t blue);
//

//~~~~~get pixel components~~~~~~~~~~~~~~~~~
    //returns `blue` components from pix given
    __uint8_t pixel_blue(const pixel_t *p);

    //returns `green` components from pix given
    __uint8_t pixel_green(const pixel_t *p);
    
    //returns `red` components from pix given
    __uint8_t pixel_red(const pixel_t *p);

    bool is_pixel_black(const pixel_t *p);

    size_t ppm_black_counter(const ppm_image_t *img);

//


//~~~~~~get ppm picture components~~~~~~~~~~~~
    
    //fills config string used in further fonctions 
    void ppm_get_config(FILE* image_file , char* config);

    //returns ppm_image `length` field (memory needed for pixel array)
    size_t get_ppm_size(FILE* image_file);

    //returns nbr of pixels/row
    size_t get_ppm_width(const char* config);

    //returns nbr of rows
    size_t get_ppm_height(const char* config);

    //returns index of file byte where pixels array starts
    __uint8_t get_ppm_start(const char* config);

    //returns a pixel_t from ppm_image_t located at {x,y}
    pixel_t ppm_get_pixel_at(const ppm_image_t *img, const size_t x, const size_t y);
//

//returns true if p and p2 are equals , false otherwise
bool pixel_equals(const pixel_t *p , const pixel_t *p2);

//returns pixel_t , negatif of origin pixel `pix`
pixel_t pixel_invert(const pixel_t* pix);

//frees ppm_image_t pixel array
void ppm_free(ppm_image_t* picture);

//creates `file`.ppm given through filepath from ppm_image
void ppm_file_from_pic(const ppm_image_t* origin , const char* filepath);

//copy all fields (pixelArray excluded) from origin to recent
void ppm_copy_attributes(ppm_image_t* recent ,const ppm_image_t* origin);
