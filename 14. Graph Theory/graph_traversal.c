#include "graph.c"
#include "../VI. Queues/circular_deque.c"

//Takes neighbours of a graph node and traverses them recursively.
void _dfs(GraphNode* s, void (*callback)(GraphNode), unsigned int* visited) {
    if(*visited&(1<<(s->graph_node_index))) { return; }
    *visited = *visited | (1<<(s->graph_node_index));

    callback(*s);
    for(int i = 0; i < vec_len(s->neighbour_list); i++) { _dfs(s->neighbour_list[i], callback, visited); }
}

void dfs(GraphNode* s, void (*callback)(GraphNode)) {
    unsigned int* visited = (unsigned int*)malloc(sizeof (unsigned int));
    _dfs(s, callback, visited);
    free(visited);
}

void _bfs(GraphNode* s, void (*callback)(GraphNode*), long int visited, int* distances, CircularQueue* q) {

}