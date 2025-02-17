#include "graph.h"
#include "queue.h"
#include "miniqutils.h"

#ifndef GRAPH_NETWORK_FLOW
#define GRAPH_NETWORK_FLOW

int graph_edmonds_karp_breadth_first_search(
        struct graph* residual_graph,
        void* source,
        void* sink,
        struct vertex** predecessor
        );

int graph_ford_fulkerson(struct graph* residual_graph, void* source, void* sink, struct vertex** predecessor);
int graph_edmonds_karp(struct graph* graph, void* source, void* sink);
int graph_max_flow(struct graph* graph, void* source, void* sink);
int graph_min_cut(struct graph* graph, void* source, void* sink, vector(struct edge*) min_cut);

int graph_max_vertex_disjoint_paths(struct graph* graph, void* source, void* sink);
int graph_max_edge_disjoint_paths(struct graph* graph, void* source, void* sink);

int graph_max_bipartite_matchings(struct graph* graph, vector(struct edge*) matching, vector(void*) minimum_vertex_cover);

#endif
