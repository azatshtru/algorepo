#include "graph_traversal.c"
#include "../VI. Queues/priority_queue.c"
#include "../V. Sets and Iterators/union_find_structure.c"

#define INFINITY_32BIT 2147483647

int8 graph_edge_compare_by_weight(void* a, void* b) {
    return (*(GraphEdge*)a).weight < (*(GraphEdge*)b).weight?-1:0;
}

void graph_edge_println(GraphEdge edge) {
    printf("\n%c-%c: %d", edge.node_a->value, edge.node_b->value, edge.weight);
}

EdgeListGraph graph_kruskal(AdjacencyListGraph adj_graph) {
    EdgeListGraph edge_graph = edge_list_graph_from(adj_graph);
    vec_quicksort(edge_graph, 0, vec_len(edge_graph)-1, graph_edge_compare_by_weight);

    uint8 adj_len = vec_len(adj_graph);
    uint32 link[adj_len];
    uint32 size[adj_len];
    DisjointSet set = disjoint_set_new(link, size, adj_len);

    EdgeListGraph result = edge_list_graph_new();
    for(int i = 0; i < vec_len(edge_graph); i++) {
        int a = edge_graph[i].node_a->graph_index;
        int b = edge_graph[i].node_b->graph_index;
        if(!disjoint_set_same_component(set, a, b)) { 
            disjoint_set_unite(&set, a, b);
            __vec_push__(result, edge_graph[i]); 
        }
    }

    edge_list_graph_free(edge_graph);
    return result;
}

EdgeListGraph graph_prim(AdjacencyListGraph adj_graph) {
    EdgeListGraph edge_graph = edge_list_graph_new();
    PriorityQueue q = priority_queue_new();
    boolean processed[vec_len(adj_graph)+1];
    uint32 distance[vec_len(adj_graph)+1];
    for(int i = 0; i < vec_len(adj_graph); i++) { 
        distance[i] = INFINITY_32BIT;
        processed[i] = FALSE;
    }

    priority_queue_nq(q, graph_edge_new(edge_graph, NULL, adj_graph, 0, FALSE), 0);

    while(vec_len(edge_graph) < vec_len(adj_graph)-1) {
        GraphEdge* s = (GraphEdge*)priority_queue_dq(q);
        if(processed[(s->node_b)->graph_index]) { continue; }
        processed[(s->node_b)->graph_index] = TRUE;
        graph_edge_new(edge_graph, s->node_a, s->node_b, s->weight, FALSE);
        uint32 len = vec_len((s->node_b)->neighbour_list);
        for(int i = 0; i < len; i++) {
            GraphNode* u = (s->node_b)->neighbour_list[i].node;
            int weight = (s->node_b)->neighbour_list[i].weight;
            priority_queue_nq(q, graph_edge_new(edge_graph, s->node_b, u, weight, FALSE), -weight);
        }
    }

    return edge_graph;
}