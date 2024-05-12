#include "graph.c"
#include "../VI. Queues/circular_deque.c"

//Takes neighbours of a graph node and traverses them recursively.
void _dfs(GraphNode* s, void (*callback)(GraphNode), unsigned int* visited) {
    if(*visited&(1<<(s->graph_index))) { return; }
    *visited = *visited | (1<<(s->graph_index));

    callback(*s);
    for(int i = 0; i < vec_len(s->neighbour_list); i++) { _dfs(s->neighbour_list[i], callback, visited); }
}

//O(n)
void dfs(GraphNode* s, void (*callback)(GraphNode)) {
    unsigned int* visited = (unsigned int*)malloc(sizeof (unsigned int));
    _dfs(s, callback, visited);
    free(visited);
}

//Add the origin_node to a queue, process it and add its neighbours to the queue as well.
//Sequentially, process every node on the queue, while adding its neighbours to the queue.
//Once a node is processed, pop it off the queue.
void _bfs(AdjacencyListGraph graph, GraphNode* origin_node, void (*callback)(GraphNode), int* visited, int* distance, CircularQueue* q) {
    uint8 x = origin_node->graph_index; // get the index of origin node
    distance[x] = 0; // set the distance of origin node to zero.
    visited[x] = 1; // set visited of origin node to true and add index of origin node to the queue.
    queue_push_rear(q, x);
    while(!queue_is_empty(q)) {
        uint8 s_index = queue_pop_front(q); // get index of next node in queue and pop it off the queue.
        GraphNode s = graph[s_index]; // get the next node in queue from index.
        callback(s); // process the node.
        for(int i = 0; i < vec_len(s.neighbour_list); i++) { // add neighbours of the node to the queue if not already added.
            GraphNode* u = s.neighbour_list[i]; // get the address of neighbour node.
            if(visited[u->graph_index]) { continue; } // if node already in queue (i.e. visited[i]==1), then continue. 
            visited[u->graph_index] = 1; // set visited[i]=1 because node is about to be added to the queue.
            distance[u->graph_index] = distance[s_index] + 1; // the distance of this neighbour node is the distance of current node + 1
            queue_push_rear(q, u->graph_index); // add the neighbour node's index to the queue
        }
    }
}

//O(n)
void bfs(AdjacencyListGraph graph, GraphNode* origin_node, void (*callback)(GraphNode)) {
    int visited[vec_len(graph)];
    memset(visited, 0, vec_len(graph)*sizeof(int));
    int distance[vec_len(graph)];
    CircularQueue q = queue_new();
    _bfs(graph, origin_node, callback, visited, distance, &q);
    queue_free(&q);
}