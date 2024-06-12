#include "graph_traversal.c"
#include "../V. Sets and Iterators/union_find_structure.c"

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
    for(int i = 0; i < vec_len(edge_graph); i++) {
        int a = edge_graph[i].node_a->graph_index;
        int b = edge_graph[i].node_b->graph_index;
        if(!disjoint_set_same_component(set, a, b)) { disjoint_set_unite(&set, a, b); }
        else { __vec_pop__(GraphEdge, edge_graph, i); }
    }

    return edge_graph;
}