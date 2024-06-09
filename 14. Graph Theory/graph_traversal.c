#include "graph.c"
#include "../VI. Queues/circular_deque.c"

//Takes neighbours of a graph node and traverses them recursively.
void _dfs(GraphNode* s, void (*callback)(GraphNode), unsigned int* visited) {
    if(*visited&(1<<(s->graph_index))) { return; }
    *visited = *visited | (1<<(s->graph_index));

    callback(*s);
    for(int i = 0; i < vec_len(s->neighbour_list); i++) { _dfs(s->neighbour_list[i].node, callback, visited); }
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
void _bfs(AdjacencyListGraph graph, GraphNode* origin_node, void (*callback)(GraphNode), uint8* visited, int* distance, CircularQueue* q) {
    uint8 x = origin_node->graph_index; // get the index of origin node
    distance[x] = 0; // set the distance of origin node to zero
    visited[x] = 1; // set visited of origin node to true 
    queue_push_rear(q, x); //add index of origin node to the queue
    while(!queue_is_empty(q)) {
        uint8 s_index = queue_pop_front(q); // get index of next node in queue and pop it off the queue.
        GraphNode s = graph[s_index]; // get the next node in queue from index.
        callback(s); // process the node.
        for(int i = 0; i < vec_len(s.neighbour_list); i++) { // add neighbours of the node to the queue if not already added.
            GraphNode u = *s.neighbour_list[i].node; // get the address of neighbour node.
            if(visited[u.graph_index]) { continue; } // if node already in queue (i.e. visited[i]==1), then continue. 
            visited[u.graph_index] = 1; // set visited[i]=1 because node is about to be added to the queue.
            distance[u.graph_index] = distance[s_index] + 1; // the distance of this neighbour node is the distance of current node + 1
            queue_push_rear(q, u.graph_index); // add the neighbour node's index to the queue
        }
    }
}

//O(n)
void bfs(AdjacencyListGraph graph, GraphNode* origin_node, void (*callback)(GraphNode)) {
    uint8 visited[vec_len(graph)];
    memset(visited, 0, vec_len(graph)*sizeof(uint8));
    int distance[vec_len(graph)];
    CircularQueue q = queue_new();
    _bfs(graph, origin_node, callback, visited, distance, &q);
    queue_free(&q);
}

//Applications: Connectivity check, whether it possible to reach every node staring with any node.
void _graph_connectivity_check(GraphNode* s, uint8* visited, uint8* node_count) {
    if(visited[s->graph_index]) { return; }
    visited[s->graph_index] = 1;
    *node_count += 1;
    for(int i = 0; i < vec_len(s->neighbour_list); i++) {
        _graph_connectivity_check(s->neighbour_list[i].node, visited, node_count);
    }
}

boolean graph_connectivity_check(AdjacencyListGraph graph) {
    GraphNode* origin_node = graph+0;
    uint8 visited[vec_len(graph)];
    memset(visited, 0, sizeof(uint8)*vec_len(graph));
    uint8 node_count = 0;
    _graph_connectivity_check(origin_node, visited, &node_count);
    return node_count == vec_len(graph);
}

//Applications: Finding cycles
boolean graph_cycle_check(GraphNode* s, GraphNode* prev, uint32 visited) {
    if(visited&(1<<s->graph_index)) {
        return 1;
    }
    visited |= (1<<s->graph_index);
    uint8 cycle_flag = 0;
    for(int i = 0; i < vec_len(s->neighbour_list); i++) { 
        if(s->neighbour_list[i].node == prev) { continue; }
        cycle_flag += graph_cycle_check(s->neighbour_list[i].node, s, visited);
    }
    return cycle_flag;
}

//Applications: Bipartiteness check, check if the graph can be colored using two colors such that no two adjacent nodes have the same color.
boolean graph_bipartiteness_check(AdjacencyListGraph graph) {
    GraphNode origin_node = graph[0];

    uint8 colors[vec_len(graph)];
    colors[0] = 1;

    uint8 visited[vec_len(graph)];
    memset(visited, 0, sizeof(uint8)*vec_len(graph));

    CircularQueue q = queue_new();

    queue_push_rear(&q, origin_node.graph_index);
    visited[0] = 1;

    while(!queue_is_empty(&q)) {
        GraphNode s = graph[queue_pop_front(&q)];
        for(int i = 0; i < vec_len(s.neighbour_list); i++) {
            GraphNode* u = s.neighbour_list[i].node;
            uint8 u_index = u->graph_index;
            if(visited[u_index]) { 
                if(colors[u_index] != !colors[s.graph_index]) {
                    return 0;
                }
                continue;
            }
            visited[u_index] = 1;
            colors[u_index] = !colors[s.graph_index];
            queue_push_rear(&q, u_index);
        }
    }
    return 1;
}