#include "../headers/graph.h"
#include "../headers/queue.h"
#include "../headers/priority_queue.h"
#include "../headers/miniqutils.h"

#ifndef ACYCLIC_GRAPH
#define ACYCLIC_GRAPH

#define PROCESSING 1
#define PROCESSED 2

int acyclic_graph_topological_depth_first_search(struct vertex* v, int* state, struct vertex** topological_order, int topological_order_index) {
    if(state[v->i] == PROCESSED) { return 1; }
    if(state[v->i] == PROCESSING) { return 0; }
    int is_acyclic;
    state[v->i] = PROCESSING;
    for(int i = 0; i < graph_vertex_out_degree(v); i++) {
        struct vertex* u = vec_get(v->out, i);
        is_acyclic = acyclic_graph_topological_depth_first_search(u, state, topological_order, topological_order_index);
        if(is_acyclic == 0) { break; }
    }
    state[v->i] = PROCESSED;
    if(topological_order != NULL) {
        topological_order[topological_order_index++] = v;
    }
    return is_acyclic;
}

int acyclic_graph_toplogical_sort(struct graph* graph, struct vertex** topological_order) {
    int vertex_len = graph_vertices_len(graph);
    int state[vertex_len];
    for(int i = 0; i < vertex_len; i++) {
        state[i] = 0;
    }
    for(int i = 0; i < vertex_len; i++) {
        if(state[i] != 0) { continue; }
        if(acyclic_graph_topological_depth_first_search(graph_vertex_from_i(graph, i), state, topological_order, 0)) {
            continue;
        } else {
            return 1;
        }
    }
    for(int i = 0, j = vertex_len - 1; i < j; i++, j--) {
        swap(topological_order + i, topological_order + j, sizeof(struct vertex*));
    }
    return 0;
}

int acyclic_graph_paths_to(struct graph* graph, struct vertex* s, struct vertex* current, int* paths, int* visited) {
    if(visited[current->i]) {
        return paths[current->i];
    }
    visited[current->i] = 1;
    if(current == s) {
        return 1;
    }
    int pathsum = 0;
    for(int i = 0; i < graph_vertex_out_degree(current); i++) {
        struct vertex* u = vec_get(current->out, i);
        pathsum += acyclic_graph_paths_to(graph, s, u, paths, visited);
    }
    paths[current->i] = pathsum;
    return pathsum;
}

int acyclic_graph_paths_between(struct graph* graph, struct vertex* from, struct vertex* to) {
    int vertex_len = graph_vertices_len(graph);
    int paths[vertex_len];
    int visited[vertex_len];
    for(int i = 0; i < vertex_len; i++) { 
        paths[i] = 0;
        visited[i] = 0;
    }
    paths[to->i] = 1;

    acyclic_graph_paths_to(graph, to, from, paths, visited);

    return paths[from->i];
}

void graph_dijkstra_acyclic_product(AdjacencyListGraph graph, uint8 starting_node_index, AdjacencyListGraph* acyclic_graph) {
    int32 distance[vec_len(graph)];
    boolean processed[vec_len(graph)];
    PriorityQueue q = priority_queue_new();
    uint8* prev_path_node[vec_len(graph)];

    for(int i = 0; i < vec_len(graph); i++) { 
        distance[i] = INFINITY_8BIT;
        processed[i] = FALSE;
        prev_path_node[i] = __vec_new__(uint8);
    }
    distance[starting_node_index] = 0;
    priority_queue_nq(q, &starting_node_index, 0);

    while(vec_len(q)) {
        uint8 a = *(uint8*)priority_queue_dq(q);
        if(processed[a]) { continue; }
        processed[a] = TRUE;
        for(uint8 i = 0; i < vec_len(graph[a].neighbour_list); i++) {
            GraphNode* neighbour = graph[a].neighbour_list[i].node;
            int32 w = graph[a].neighbour_list[i].weight;
            if(distance[a]+w < distance[neighbour->graph_index]) {
                distance[neighbour->graph_index] = distance[a]+w;
                priority_queue_nq(q, &neighbour->graph_index, -distance[neighbour->graph_index]);
                vec_clear(prev_path_node[neighbour->graph_index]);
                __vec_push__(prev_path_node[neighbour->graph_index], a);
            }
            if(distance[a]+w == distance[neighbour->graph_index]) {
                __vec_push__(prev_path_node[neighbour->graph_index], a);
            }
        }
    }

    for(int i = 0; i < vec_len(graph); i++) { graph_node_new(acyclic_graph, graph[i].value); }
    for(int i = 0; i < vec_len(graph); i++) {
        for(int j = 0; j < vec_len(prev_path_node[i]); j++) {
            graph_node_add_neighbours((*acyclic_graph)+prev_path_node[i][j], FALSE, 1, (*acyclic_graph)+i, 1);
        }
    }
    for(int i = 0; i < vec_len(graph); i++) { vec_free(prev_path_node[i], NULL); }
}

//Similar to dijkstra's acyclic product, all dynamic programming problems result in an acyclic graph where
//each node represents a state and the edges represent a path taken from that state.

uint8 logb2(uint8 x) {
    uint8 log = 0;
    while(x>>=1) {++log;}
    return log; 
}

GraphNode* graph_succ(GraphNode* node) {
    return node->neighbour_list[0].node;
}

uint8 _graph_precalculate_succ(AdjacencyListGraph* successor_graph, uint8 x, uint8 limit, uint8** succ) {
    succ[logb2(limit)][x] = limit == 1 ? (*successor_graph)[x].neighbour_list[0].node->graph_index 
        : _graph_precalculate_succ(successor_graph, _graph_precalculate_succ(successor_graph, x, limit/2, succ), limit/2, succ);
    return succ[logb2(limit)][x];
}

void graph_precalculate_succ(AdjacencyListGraph successor_graph, uint8 limit, uint8** succ) {
    for(int i = 0; i < vec_len(successor_graph); i++) {
        _graph_precalculate_succ(&successor_graph, i, limit, succ);
    }
}

uint8 graph_kth_succsessor(uint8 x, uint8 k, uint8** succ) {
    uint8 result = k;
    while(k > 0) {
        result = succ[logb2(k)][x];
        k /= 2;
    }
    return result;
}

void graph_floyd_tortoise_and_hair(AdjacencyListGraph* successor_graph, uint8* first_node_of_cycle, uint8* length_of_cycle) {
    //cycle detection
    GraphNode* a = graph_succ(*successor_graph);
    GraphNode* b = graph_succ(graph_succ(*successor_graph));
    while(a != b) {
        a = graph_succ(a);
        b = graph_succ(graph_succ(b));
    }

    //first node of cycle
    a = *successor_graph;
    while(a != b) {
        a = graph_succ(a);
        b = graph_succ(b);
    }
    *first_node_of_cycle = a->graph_index;

    //length of cycle
    b = graph_succ(a);
    uint8 length = 1;
    while (a != b) {
        b = graph_succ(b);
        ++length;
    }
    *length_of_cycle = length;
}

#endif
