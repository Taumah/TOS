#include "../headers/functions.h"
#include "../headers/commons.h"

#define MAX_THREADS 2

int main(/*int argc, char** argv*/){                                                                                                            

    // ppm_image_t second_picture = ppm_new("small.ppm");
    shared_counter_t * shared_counter = shared_counter_new();

    thread_data_t thr_data[MAX_THREADS];
    pthread_t threads[MAX_THREADS];

    ppm_image_t picture = ppm_new("small.ppm");
    ppm_image_t copy = ppm_revert(&picture);

    ppm_image_t picture2 = ppm_new("testppm.ppm");
    // pixel_t test = {20, 30 ,40};

    // ppm_print(&copy);

    // ppm_file_from_pic(&picture , "picture.ppm");
    // ppm_file_from_pic(&copy , "copy.ppm");

    printf("il y a %lu pixel(s) noirs \n\n\n\n" , ppm_black_counter(&copy));

    ppm_free(&picture);
    ppm_free(&copy);

    for (int32_t i = 0; i < MAX_THREADS; i += 1) {
        thr_data[i].thread_id = i;
        // Take a pointer to shared counter
        thr_data[i].shared_counter = shared_counter;

        int32_t failure_reason = pthread_create(&threads[i], NULL, run, &thr_data[i]);
        if (failure_reason) {
            fprintf(stderr, "Error: pthread_create, rc: %d\n", failure_reason);
            return EXIT_FAILURE;
        }

        ppm_black_counter_with_multithread(&picture2 , &thr_data[i]);

    }
    printf("il y a %u pixel(s) noirs apres calcul via les threads\n\n\n\n" , shared_counter->counter);
    //je pense que le calcul ne fonctionne que si l'image est suffisamment grande
    // car parfois la boucle de création des threads se termine AVANT que les threads eux mêmes aient pu faire leur travail



    shared_counter_drop(shared_counter);    

    return 0;


}

void* run(void* args){
    thread_data_t * data = (thread_data_t *) args;

    printf("start counting... thread %d\n" , data->thread_id);

    return args;
}

