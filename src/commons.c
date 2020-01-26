#include "../headers/commons.h"

bool is_whitespace(const char letter){
    return (strchr("\t\n\v\f\r " , letter) == NULL);
}