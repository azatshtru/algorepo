#include "common_collections/include/vector.h"

int main() {
    vector(int) v = vec_new(int);
    vec_push(v, 21);
    vec_push(v, 5);
    vec_push(v, 87);
    vec_push(v, 7);
    vec_push(v, 69);
    vec_push(v, 400);

    int a = vec_pop(v, -1);
    int b = vec_pop(v, 2);
    int c = vec_pop(v, 2);

    vec_print_primitive(v, "%d");

    vec_free(v, NULL);

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);

    return 0;
}
