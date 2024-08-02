#include "headers/array_utils.h"
#include "common_collections/include/vector.h"

int main() {
    vector(int) v = vec_new(int);

    vec_push(v, 6);
    vec_push(v, 8);
    vec_push(v, -8);
    vec_print_primitive(v, "%d");

    return 0;
}