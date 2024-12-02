#include "headers/queue.h"
#include <stdio.h>

int main() {
    VecDeque(int) qi = queue_new(int);

    queue_push_front(qi, 5);
    queue_push_front(qi, 15);
    queue_push_back(qi, 69);
    queue_push_front(qi, 24);
    queue_push_front(qi, -46);
    queue_push_back(qi, 12);
    queue_push_back(qi, -6);

    int a = queue_pop_front(qi);
    int b = queue_pop_back(qi);
    int c = queue_pop_back(qi);
    queue_push_front(qi, 61);

    queue_print_primitive(qi, "%d");

    queue_free(qi, NULL);

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);

    return 0;
}
