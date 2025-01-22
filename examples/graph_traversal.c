#include "../headers/queue.h"
#include "../headers/graph.h"

void graph_breadth_first_search(struct graph* graph, struct vertex* origin) {
    size_t vertices_len_in_bytes = sizeof(unsigned int) * graph_vertices_len(graph);
    unsigned int distance[vertices_len_in_bytes];
    unsigned int visited[vertices_len_in_bytes];
    memzero(distance, vertices_len_in_bytes);
    memzero(visited, vertices_len_in_bytes);

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
    struct graph g = graph_new();
    struct vertex_int v1;
    vertex_int_init(&v1, &g, 0);
    struct vertex_int v2;
    vertex_int_init(&v2, &g, 1);
    struct vertex_int v3;
    vertex_int_init(&v3, &g, 2);
    struct vertex_int v4;
    vertex_int_init(&v4, &g, 3);
    struct vertex_int v5;
    vertex_int_init(&v5, &g, 4);
    struct vertex_int v6;
    vertex_int_init(&v6, &g, 5);
    struct vertex_int v7;
    vertex_int_init(&v7, &g, 6);

    struct edge e1;
    graph_add_edge(&g, &e1, &v1.v, &v2.v);
    struct edge e2;
    graph_add_edge(&g, &e2, &v1.v, &v3.v);
    struct edge e3;
    graph_add_edge(&g, &e3, &v2.v, &v4.v);
    struct edge e4;
    graph_add_edge(&g, &e4, &v2.v, &v5.v);
    struct edge e5;
    graph_add_edge(&g, &e5, &v3.v, &v6.v);
    struct edge e6;
    graph_add_edge(&g, &e6, &v4.v, &v7.v);
    struct edge e7;
    graph_add_edge(&g, &e7, &v6.v, &v7.v);


    graph_breadth_first_search(&g, &v1.v); // 0 1 2 3 4 5 6
    printf("\n");

    graph_breadth_first_search(&g, &v3.v); // 2 5 6
    printf("\n");

    graph_breadth_first_search(&g, &v4.v); // 3 6
    printf("\n");

    graph_breadth_first_search(&g, &v7.v); // 6
    printf("\n");
    

    size_t vertices_len_in_bytes = sizeof(unsigned int) * graph_vertices_len(&g);
    unsigned int visited[vertices_len_in_bytes];

    memzero(visited, vertices_len_in_bytes);
    graph_depth_first_search(&g, &v1.v, visited); // 0 1 3 6 4 2 5
    printf("\n");

    memzero(visited, vertices_len_in_bytes);
    graph_depth_first_search(&g, &v3.v, visited); // 2 5 6
    printf("\n");

    memzero(visited, vertices_len_in_bytes);
    graph_depth_first_search(&g, &v4.v, visited); // 3 6
    printf("\n");

    memzero(visited, vertices_len_in_bytes);
    graph_depth_first_search(&g, &v7.v, visited); // 6
    printf("\n");

    graph_free(&g);

    return 0;
}
