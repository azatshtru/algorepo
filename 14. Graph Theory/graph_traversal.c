#include "graph.c"

//Takes neighbours of a graph node and traverses them recursively.
void dfs(GraphNode* s, void (*callback)(GraphNode*), long int visited) {
    if(visited&(1<<s->graph_index)) { return; }
    visited = visited | (1<<s->graph_index);

    callback(s);
    for(int i = 0; i < s->neighbour_len; i++) { dfs(s->neighbour_list[i], callback, visited); }
}

void bfs(GraphNode* s, void (*callback)(GraphNode*), long int visited) {

}