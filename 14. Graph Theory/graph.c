#include <stdlib.h>

typedef union graph_node_value_type {

} GraphNodeT;

typedef struct graph_node {
    float value;
    struct graph_node* neighbour_list;
} GraphNode;

typedef struct adjacency_list_graph {
    int size;
    int capacity;
    GraphNode* node_list;
} AdjacencyListGraph;

AdjacencyListGraph newAdjacencyListGraph(int capacity) {
    GraphNode* node_list = (GraphNode*)malloc(sizeof(GraphNode)*capacity);
    AdjacencyListGraph graph = { -1, capacity, node_list };
    return graph;
}

void resizeAdjacencyListGraph(AdjacencyListGraph* graph_ptr, int capacity) {
    GraphNode* newNodeList = (GraphNode*)malloc(sizeof(GraphNode)*capacity);
    for(int i = 0; i < graph_ptr->capacity; i++) { newNodeList[i] = graph_ptr->node_list[i]; }
    free(graph_ptr->node_list);
    AdjacencyListGraph newGraph = { graph_ptr->size, capacity, newNodeList };
    *graph_ptr = newGraph;
}

GraphNode* newGraphNode(AdjacencyListGraph* graph_ptr, float value, GraphNode* neighbour_list) {
    if(graph_ptr->capacity - 1 == graph_ptr->size) { 
        printf("Adj Graph %p full, doing nothing.", graph_ptr);
        return NULL;
    }
    graph_ptr->node_list[++graph_ptr->size].value = value;
    if(neighbour_list != NULL) { graph_ptr->node_list[graph_ptr->size].neighbour_list = neighbour_list; }
    return graph_ptr->node_list+graph_ptr->size;
}

void freeAdjacencyListGraph(AdjacencyListGraph* graph_ptr) { free(graph_ptr->node_list); }

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

EdgeListGraph newEdgeListGraph(int capacity) {
    GraphEdge* edge_list = (GraphEdge*)malloc(sizeof(GraphEdge)*capacity);
    EdgeListGraph graph = { -1, capacity, edge_list };
    return graph;
}

void resizeEdgeListGraph(EdgeListGraph* graph_ptr, int capacity) {
    GraphEdge* newEdgeList = (GraphEdge*)malloc(sizeof(GraphEdge)*capacity);
    for(int i = 0; i < graph_ptr->capacity; i++) { newEdgeList[i] = graph_ptr->edge_list[i]; }
    free(graph_ptr->edge_list);
    EdgeListGraph newGraph = { graph_ptr->size, capacity, newEdgeList };
    *graph_ptr = newGraph;
}

GraphEdge* newGraphEdge(EdgeListGraph* graph_ptr, GraphNode* node_a, GraphNode* node_b, int weight) {
    if(graph_ptr->capacity - 1 == graph_ptr->size) { 
        printf("Edge Graph %p full, doing nothing.", graph_ptr);
        return NULL;
    }
    graph_ptr->edge_list[++graph_ptr->size].weight = weight;
    graph_ptr->edge_list[graph_ptr->size].node_a = node_a;
    graph_ptr->edge_list[graph_ptr->size].node_b = node_b;
    return graph_ptr->edge_list+graph_ptr->size;
}

void freeEdgeListGraph(EdgeListGraph* graph_ptr) { free(graph_ptr->edge_list); }

typedef struct adjacency_matrix_graph {
    int** weight_matrix;
    int n;
} AdjacencyMatrixGraph;

AdjacencyMatrixGraph newAdjacencyMatrixGraph(int n) {
    int** weight_matrix = (int**)malloc(sizeof(int*)*n);
    for(int i = 0; i < n; i++) { weight_matrix[i] = (int*)malloc(sizeof(int)*n); }
    AdjacencyMatrixGraph graph = { weight_matrix, n };
    return graph;
}

void freeAdjacencyMatrixGraph(AdjacencyMatrixGraph* graph_ptr) {
    for(int i = 0; i < graph_ptr->n; i++) { free(graph_ptr->weight_matrix[i]); }
    free(graph_ptr->weight_matrix);
}