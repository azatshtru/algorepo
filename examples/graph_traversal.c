#include "../headers/queue.h"
#include "../headers/graph.h"

void graph_breadth_first_search(struct graph* graph, void* origin) {
    size_t vertices_len = graph_vertices_len(graph);
    unsigned int distance[vertices_len];
    unsigned int visited[vertices_len];
    memzero(distance, vertices_len * sizeof(unsigned int));
    memzero(visited, vertices_len * sizeof(unsigned int));

    VecDeque(int) queue = queue_new(int);

    int x = graph_vertex_i(graph, origin);
    distance[x] = 0;
    visited[x] = 1;
    queue_push_back(queue, x);

    while(!queue_is_empty(queue)) {
        int index = queue_pop_front(queue);
        struct vertex* s = graph_vertex(graph, graph_vertex_from_i(graph, index));

        printf("BFS: %d\n", *(int*)s);

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

    printf("DFS: %d\n", *(int*)s);
    for(int i = 0; i < graph_vertex_out_degree(graph, s->value); i++) {
        graph_depth_first_search(graph, vec_get(s->out, i), visited);
    }
}

int main() {
    struct graph g = graph_new();
    int v1 = 0;
    int v2 = 1;
    int v3 = 2;
    int v4 = 3;
    int v5 = 4;
    int v6 = 5;
    int v7 = 6;

    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v1, &v3, 1);
    graph_add_edge(&g, &v2, &v4, 1);
    graph_add_edge(&g, &v2, &v5, 1);
    graph_add_edge(&g, &v3, &v6, 1);
    graph_add_edge(&g, &v4, &v7, 1);
    graph_add_edge(&g, &v6, &v7, 1);


    graph_breadth_first_search(&g, &v1); // 0 1 2 3 4 5 6
    printf("\n");

    graph_breadth_first_search(&g, &v3); // 2 5 6
    printf("\n");

    graph_breadth_first_search(&g, &v4); // 3 6
    printf("\n");

    graph_breadth_first_search(&g, &v7); // 6
    printf("\n");
    

    size_t vertices_len = graph_vertices_len(&g);
    unsigned int visited[vertices_len];

    memzero(visited, vertices_len * sizeof(unsigned int));
    graph_depth_first_search(&g, graph_vertex(&g, &v1), visited); // 0 1 3 6 4 2 5
    printf("\n");

    memzero(visited, vertices_len * sizeof(unsigned int));
    graph_depth_first_search(&g, graph_vertex(&g, &v3), visited); // 2 5 6
    printf("\n");

    memzero(visited, vertices_len * sizeof(unsigned int));
    graph_depth_first_search(&g, graph_vertex(&g, &v4), visited); // 3 6
    printf("\n");

    memzero(visited, vertices_len * sizeof(unsigned int));
    graph_depth_first_search(&g, graph_vertex(&g, &v7), visited); // 6
    printf("\n");

    graph_free(&g);

    return 0;
}
