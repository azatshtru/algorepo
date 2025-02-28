#include "../headers/graph.h"
#include "../headers/logging.h"

// merging data structures using offline algorithms

struct subtree_modal_value_int2int_map {
    int k;
    int v;
};

unsigned int subtree_modal_value_map_hash(void* x) {
    int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    unsigned int hash = 0;
    int n = ((struct subtree_modal_value_int2int_map*)x)->k;
    for(int i = 0; i < 10; i++) {
        hash += (n * primes[i]) % (i + 1);
    }
    return hash;
}

int subtree_modal_value_map_cmp(void* x, void* y) {
    return ((struct subtree_modal_value_int2int_map*)x)->k
        == ((struct subtree_modal_value_int2int_map*)y)->k;
}

hashset(struct subtree_modal_value_int2int_map) subtree_modal_value_offline_dfs(
    struct graph* tree,
    struct graph* map,
    void* current,
    void* parent,
    int* visited,
    hashset(struct subtree_modal_value_int2int_map)* vertex2map
) {
    struct vertex* s = graph_vertex(tree, current);
    if(visited[s->i]) return NULL;
    visited[s->i] = 1;

    if(vec_len(s->out) == 1) {
        hashset(struct subtree_modal_value_int2int_map) leaf = hashset_new(
            struct subtree_modal_value_int2int_map,
            subtree_modal_value_map_hash,
            subtree_modal_value_map_cmp
        );
        struct subtree_modal_value_int2int_map data = { *(int*)current, 1 };
        hashset_insert(leaf, data);
        graph_add_vertex(map, leaf);
        vertex2map[s->i] = leaf;
        return leaf;
    }


    hashset(struct subtree_modal_value_int2int_map) largest = NULL;
    hashset(struct subtree_modal_value_int2int_map) children[vec_len(s->out)];
    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value == parent) {
            children[i] = NULL;
            continue;
        }
        hashset(struct subtree_modal_value_int2int_map) child = subtree_modal_value_offline_dfs(tree, map, u->value, current, visited, vertex2map);
        if(largest == NULL || hashset_len(largest) < hashset_len(child)) {
            largest = child;
        }
        children[i] = child;
    }


    hashset(struct subtree_modal_value_int2int_map) s1 = hashset_clone(largest); 
    struct subtree_modal_value_int2int_map data = { *(int*)current, 1 };
    if(hashset_contains(s1, data)) {
        data.v += hashset_get(s1, data).v;
    }
    hashset_insert(s1, data);
    graph_add_vertex(map, s1);
    vertex2map[s->i] = s1;

    for(int i = 0; i < vec_len(s->out); i++) {
        if(children[i] == NULL) continue;
        graph_add_edge(map, s1, children[i], 1);
        if(children[i] == largest) continue;
        unsigned int j = 0;
        for(int k = 0; k < hashset_len(children[i]); k++) {
            j = hashset_lazy_iterate(children[i], j);
            struct subtree_modal_value_int2int_map value = (*children[i])[j];
            if(hashset_contains(s1, value)) {
                value.v += hashset_get(s1, value).v;
            }
            hashset_insert(s1, value);
        }
    }

    return s1;
}

void subtree_modal_value_offline(struct graph* tree, void* root) {
    unsigned int vertex_len = graph_vertices_len(tree);
    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);

    hashset(struct subtree_modal_value_int2int_map) vertex_to_map[vertex_len];

    struct graph graph = graph_new();

    subtree_modal_value_offline_dfs(tree, &graph, root, root, visited, vertex_to_map);

    for(int i = 0; i < vertex_len; i++) { 
        unsigned int j = 0;
        hashset(struct subtree_modal_value_int2int_map) x = vertex_to_map[i];
        for(int k = 0; k < hashset_len(x); k++) {
            j = hashset_lazy_iterate(x, j);
            struct subtree_modal_value_int2int_map map = (*x)[j];
            printf("subtree_modal_value_int2int_map! %d {%d, %d}\n", i + 1, map.k, map.v);
        }
    }

    graph_free(&graph);
}

int main() {
    struct graph g = graph_new();
    int things[9] = { 2, 3, 5, 3, 1, 4, 4, 3, 1 };
    for(int i = 0; i < 9; i++) {
        graph_add_vertex(&g, things + i);
    }

    graph_add_edge_symmetric(&g, things + 0, things + 1, 1);
    graph_add_edge_symmetric(&g, things + 0, things + 2, 1);
    graph_add_edge_symmetric(&g, things + 0, things + 3, 1);
    graph_add_edge_symmetric(&g, things + 0, things + 4, 1);
    graph_add_edge_symmetric(&g, things + 1, things + 5, 1);
    graph_add_edge_symmetric(&g, things + 3, things + 6, 1);
    graph_add_edge_symmetric(&g, things + 3, things + 7, 1);
    graph_add_edge_symmetric(&g, things + 3, things + 8, 1);

    subtree_modal_value_offline(&g, things + 0);

    graph_free(&g);
}
