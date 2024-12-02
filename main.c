#include "headers/queue.h"

int main() {
    Queue(int) qi = queue_new(int);

    queue_push_front(qi, 5);
    queue_push_front(qi, 15);
    queue_push_back(qi, 69);
    queue_push_front(qi, 24);
    queue_push_front(qi, -46);
    queue_push_back(qi, 12);
    queue_push_back(qi, -6);

    queue_zap_front(qi, NULL);
    queue_zap_front(qi, NULL);
    queue_zap_front(qi, NULL);
    queue_push_front(qi, 61);
    queue_zap_back(qi, NULL);

    queue_print_primitive(qi, "%d");
    
    queue_free(qi, NULL);

    return 0;
}
