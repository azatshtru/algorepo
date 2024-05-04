#include <stdlib.h>

#ifndef GRAPH
#define GRAPH

#define __graph_node_set_neighbourhood__(NODE, LEN, ...){\
GraphNode* NODE##_neighbourhood[LEN] = { __VA_ARGS__ };\
graph_node_set_neighbourhood(NODE, LEN, NODE##_neighbourhood);\
}

typedef unsigned char uint8;


typedef enum edge_sync_policy {
    edge_sync, no_edge_sync
} EDGE_SYNC_POLICY;

typedef enum graph_reflective_policy {
    reflective, non_reflective
} GRAPH_REFLECTIVE_POLICY;

typedef union graph_node_value_type {

} GraphNodeT;

typedef struct graph_node {
    struct graph_node **neighbour_list;
    uint8 neighbour_len;
    uint8 graph_index;
    short value;
} GraphNode;

typedef struct adjacency_list_graph {
    int size;
    int capacity;
    GraphNode* node_list;
} AdjacencyListGraph;

AdjacencyListGraph adjacency_list_graph_new(int capacity) {
    GraphNode* node_list = (GraphNode*)malloc(sizeof(GraphNode)*capacity);
    AdjacencyListGraph graph = { -1, capacity, node_list };
    return graph;
}

void adjacency_list_graph_resize(AdjacencyListGraph* graph_ptr, int capacity) {
    GraphNode* newNodeList = (GraphNode*)malloc(sizeof(GraphNode)*capacity);
    for(int i = 0; i < graph_ptr->capacity; i++) { newNodeList[i] = graph_ptr->node_list[i]; }
    free(graph_ptr->node_list);
    AdjacencyListGraph newGraph = { graph_ptr->size, capacity, newNodeList };
    *graph_ptr = newGraph;
}

GraphNode* graph_node_new(AdjacencyListGraph* graph_ptr, short value, GraphNode** neighbour_list) {
    if(graph_ptr->capacity - 1 == graph_ptr->size) { 
        printf("Adj Graph %p full, doing nothing.", graph_ptr);
        return NULL;
    }
    graph_ptr->node_list[++graph_ptr->size].value = value;
    graph_ptr->node_list[graph_ptr->size].graph_index = (uint8)graph_ptr->size;
    if(neighbour_list != NULL) { graph_ptr->node_list[graph_ptr->size].neighbour_list = neighbour_list; }
    return graph_ptr->node_list+graph_ptr->size;
}

void graph_node_set_neighbourhood(GraphNode* graph_node, uint8 neighbour_len, GraphNode** neighbour_list) {
    if(neighbour_list != NULL) { 
        graph_node->neighbour_len = neighbour_len;
        graph_node->neighbour_list = neighbour_list;
    }
}

void adjacency_list_graph_free(AdjacencyListGraph* graph_ptr) { free(graph_ptr->node_list); }

typedef struct graph_edge {
    GraphNode* node_a;    
    GraphNode* node_b;
    int weight;
} GraphEdge;

typedef struct edge_list_graph {
    int size;
    int capacity;
    GraphEdge* edge_list;
} EdgeListGraph;

EdgeListGraph edge_list_graph_new(int capacity) {
    GraphEdge* edge_list = (GraphEdge*)malloc(sizeof(GraphEdge)*capacity);
    EdgeListGraph graph = { -1, capacity, edge_list };
    return graph;
}

void edge_list_graph_resize(EdgeListGraph* graph_ptr, int capacity) {
    GraphEdge* newEdgeList = (GraphEdge*)malloc(sizeof(GraphEdge)*capacity);
    for(int i = 0; i < graph_ptr->capacity; i++) { newEdgeList[i] = graph_ptr->edge_list[i]; }
    free(graph_ptr->edge_list);
    EdgeListGraph newGraph = { graph_ptr->size, capacity, newEdgeList };
    *graph_ptr = newGraph;
}

GraphEdge* graph_edge_new(EdgeListGraph* graph_ptr, GraphNode* node_a, GraphNode* node_b, int weight) {
    if(graph_ptr->capacity - 1 == graph_ptr->size) { 
        printf("Edge Graph %p full, doing nothing.", graph_ptr);
        return NULL;
    }
    graph_ptr->edge_list[++graph_ptr->size].weight = weight;
    graph_ptr->edge_list[graph_ptr->size].node_a = node_a;
    graph_ptr->edge_list[graph_ptr->size].node_b = node_b;
    return graph_ptr->edge_list+graph_ptr->size;
}

void free_edge_list_graph(EdgeListGraph* graph_ptr) { free(graph_ptr->edge_list); }

typedef struct adjacency_matrix_graph {
    int** weight_matrix;
    int n;
} AdjacencyMatrixGraph;

AdjacencyMatrixGraph adjacency_matrix_graph_new(int n) {
    int** weight_matrix = (int**)malloc(sizeof(int*)*n);
    for(int i = 0; i < n; i++) { weight_matrix[i] = (int*)malloc(sizeof(int)*n); }
    AdjacencyMatrixGraph graph = { weight_matrix, n };
    return graph;
}

void adjacency_matrix_graph_free(AdjacencyMatrixGraph* graph_ptr) {
    for(int i = 0; i < graph_ptr->n; i++) { free(graph_ptr->weight_matrix[i]); }
    free(graph_ptr->weight_matrix);
}

#endif