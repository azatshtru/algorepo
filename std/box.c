#include <stdlib.h>

#define stdBox(TYPE) typedef struct box##TYPE { TYPE * value; } Box##TYPE;\
Box##TYPE createBox##TYPE (TYPE value) {\
    TYPE * pointer = (TYPE *)malloc(sizeof(TYPE));\
    *pointer = value;\
    Box##TYPE box; \
    box.value = pointer;\
    return box;\
}

#define Box(TYPE, value) createBox##TYPE(value)