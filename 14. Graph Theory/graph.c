#include <stdlib.h>
#include <stdarg.h>
#include "../std/vec.c"

#ifndef GRAPH
#define GRAPH

typedef unsigned char uint8;
typedef signed char int8;

typedef enum edge_sync_policy {
    edge_sync, no_edge_sync
} EDGE_SYNC_POLICY;

typedef enum graph_reflective_policy {
    reflective, non_reflective
} GRAPH_REFLECTIVE_POLICY;

typedef union graph_node_value_type {
    char char_value;
} GraphNodeT;

typedef struct graph_node {
    char value;
    uint8 graph_node_index;
    struct graph_node **neighbour_list;
} GraphNode;

typedef GraphNode* AdjacencyListGraph;

AdjacencyListGraph adjacency_list_graph_new() {
    AdjacencyListGraph graph = __vec_new__(GraphNode);
    return graph;
}

GraphNode* graph_node_new(AdjacencyListGraph graph, char value) {
    GraphNode graph_node = { value, vec_len(graph), __vec_new__(GraphNode*) };
    __vec_push__(graph, graph_node);
    return graph+vec_len(graph)-1;
}

void graph_node_add_neighbours(GraphNode* graph_node, int neighbour_count, ...) {
    va_list ap;
    va_start(ap, neighbour_count);
    for(uint8 i = 0; i < neighbour_count; i++) {
        __vec_push__(graph_node->neighbour_list, va_arg(ap, GraphNode*));
    }
    va_end(ap);
}

void graph_node_free(void* graph_node_voidptr) {
    GraphNode* graph_node = (GraphNode*)graph_node_voidptr;
    vec_free(graph_node->neighbour_list, NULL);
}

void graph_node_print(GraphNode graph_node) {
    printf("graph_node!{ %c: ", graph_node.value);
    for(uint8 i = 0; i < vec_len(graph_node.neighbour_list); i++) {
        printf("%c, ", graph_node.neighbour_list[i]->value);
    }
    printf("\b\b }");
}

void adjacency_list_graph_free(AdjacencyListGraph graph) { 
    vec_free(graph, graph_node_free);
}

typedef struct graph_edge {
    GraphNode* node_a;    
    GraphNode* node_b;
    int8 weight;
} GraphEdge;

typedef GraphEdge* EdgeListGraph;

EdgeListGraph edge_list_graph_new() {
    GraphEdge* graph = __vec_new__(GraphEdge);
    return graph;
}

GraphEdge* graph_edge_new(EdgeListGraph graph, GraphNode* node_a, GraphNode* node_b, int weight) {
    GraphEdge graph_edge = { node_a, node_b, weight };
    __vec_push__(graph, graph_edge);
    return graph+vec_len(graph)-1;
}

void free_edge_list_graph(EdgeListGraph graph) { vec_free(graph, NULL); }

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