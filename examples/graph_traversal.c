#include "../headers/queue.h"
#include "../headers/graph.h"

void graph_breadth_first_search(struct graph* graph, struct vertex* origin) {
    unsigned int distance[sizeof(unsigned int) * graph_vertices_len(graph)];
    unsigned int visited[sizeof(unsigned int) * graph_vertices_len(graph)];
    VecDeque(int) queue = queue_new(int);

    int x = origin->i;
    distance[x] = 0;
    visited[x] = 1;
    queue_push_back(queue, x);

    while(!queue_is_empty(queue)) {
        int index = queue_pop_front(queue);
        struct vertex* s = graph_vertex_from_i(graph, index);

        printf("BFS: %d\n", vertex_int_value(s));

        for(int i = 0; i < vec_len(s->out); i++) {
            struct vertex* u = vec_get(s->out, i);
            if(visited[u->i]) { continue; }
            visited[u->i] = 1;
            distance[u->i] = distance[index] + 1;
            queue_push_back(queue, u->i);
        }
    }
}

void graph_depth_first_search(struct graph* graph, struct vertex* s, unsigned int* visited) {
    if(visited[s->i]) { return; }
    visited[s->i] = 1;

    printf("DFS: %d\n", vertex_int_value(s));
    for(int i = 0; i < graph_vertex_out_degree(s); i++) {
        graph_depth_first_search(graph, vec_get(s->out, i), visited);
    }
}

int main() {
    return 0;
}
