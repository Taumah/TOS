typedef struct pixel_t
{
    __uint8_t red;
    __uint8_t green;
    __uint8_t blue;
} pixel_t;

typedef struct ppm_image_t{
    size_t height;
    size_t width;
    


}ppm_image_t;


__uint8_t img_blue(const pixel_t *p);
__uint8_t img_red(const pixel_t *p);
__uint8_t img_green(const pixel_t *p);


bool img_blue(const pixel_t *p)