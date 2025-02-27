#include "../headers/tree.h"

// a tree is a graph that has n nodes and n - 1 edges
// each node except the root has only one parent
// there exist only unique paths between any two nodes

int graph_is_tree(struct graph* graph, void** parent) {
    unsigned int vertex_len = graph_vertices_len(graph);
    int visited[vertex_len];
    int count = 0;
    memzero(visited, sizeof(int) * vertex_len);

    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    struct vertex* s = graph_vertex(graph, vec_get(graph->vertices, 0));
    parent[s->i] = NULL;
    visited[s->i] = 1;
    queue_push_back(q, s);
    
    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q);
        count++;
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            parent[v->i] = u->value;
            if(v->value == parent[u->i]) continue;
            if(visited[v->i]) return 0;
            visited[u->i] = 1;
            queue_push_back(q, vec_get(u->out, i));
        }
    }

    if(count != vertex_len) return 0;

    return 1;
}

void tree_subtree_size(struct graph* graph, void* current, void* prev, int* size) {
    struct vertex* s = graph_vertex(graph, current);
    size[s->i] = 1;
    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value == prev) continue;
        tree_subtree_size(graph, u->value, current, size);
        size[s->i] += size[u->i];
    }
}

void tree_parent(struct graph* tree, void* current, void* prev, void** parent) {
    struct vertex* s = graph_vertex(tree, current);
    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value != prev) {
            parent[u->i] = s->value;
            tree_parent(tree, u->value, current, parent);
        }
    }
}

void tree_furthest_leaf_distance(
    struct graph* graph,
    void* current, 
    int* primary_distance,
    int* visited,
    void* prev,
    int* secondary_distance,
    void** next
) {
    struct vertex* s = graph_vertex(graph, current);
    if(visited[s->i]) return;
    visited[s->i] = 1;
    int primary_max = 0;
    int secondary_max = 0;
    void* next_i;

    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        int weight = graph_edge_weight(graph, s->value, u->value);

        if(u->value == prev) continue;

        tree_furthest_leaf_distance(graph, u->value, primary_distance, visited, current, secondary_distance, next);
        if(primary_distance[u->i] + weight >= primary_max) {
            secondary_max = primary_max;
            primary_max = primary_distance[u->i] + weight;
            next_i = u->value;
            continue;
        }
        if(primary_distance[u->i] + weight >= secondary_max) {
            secondary_max = primary_distance[u->i] + weight;
        }
    }
    primary_distance[s->i] = primary_max;
    if(secondary_distance != NULL) { secondary_distance[s->i] = secondary_max; }
    if(next != NULL) { next[s->i] = next_i; }
}

int tree_longest_path_from_vertex(struct graph* graph, void* query) {
    unsigned int tree_size = graph_vertices_len(graph);
    int* distance = malloc(sizeof(int) * tree_size);
    int* visited = malloc(sizeof(int) * tree_size);
    memset(distance, 0, tree_size * sizeof(int));
    memset(visited, 0, tree_size * sizeof(int));

    tree_furthest_leaf_distance(graph, query, distance, visited, NULL, NULL, NULL);
    int query_distance = distance[graph_vertex_i(graph, query)];

    free(distance);
    free(visited);

    return query_distance;
}

int tree_longest_path_through_vertex(struct graph* graph, void* query) {
    unsigned int tree_size = graph_vertices_len(graph);
    int* primary_distance = malloc(sizeof(int) * tree_size);
    int* secondary_distance = malloc(sizeof(int) * tree_size);
    int* visited = malloc(sizeof(int) * tree_size);
    memset(primary_distance, 0, tree_size * sizeof(int));
    memset(secondary_distance, 0, tree_size * sizeof(int));
    memset(visited, 0, tree_size * sizeof(int));

    tree_furthest_leaf_distance(graph, query, primary_distance, visited, NULL, secondary_distance, NULL);
    int max_1 = primary_distance[graph_vertex_i(graph, query)];
    int max_2 = secondary_distance[graph_vertex_i(graph, query)];

    free(primary_distance);
    free(visited);
    free(secondary_distance);

    return max_1 + max_2;
}

void tree_all_longest_paths(struct graph* tree, int* longest_path) {
    unsigned int tree_size = graph_vertices_len(tree);
    int* primary_distance = malloc(sizeof(int) * tree_size);
    int* secondary_distance = malloc(sizeof(int) * tree_size);
    int* visited = malloc(sizeof(int) * tree_size);
    void** next = malloc(sizeof(void*) * tree_size);
    void** parent = malloc(sizeof(void*) * tree_size);

    memset(primary_distance, 0, tree_size * sizeof(int));
    memset(secondary_distance, 0, tree_size * sizeof(int));
    memset(visited, 0, tree_size * sizeof(int));
    memset(next, 0, tree_size * sizeof(void*));
    memset(parent, 0, tree_size * sizeof(void*));

    tree_furthest_leaf_distance(tree, vec_get(tree->vertices, 0), primary_distance, visited, NULL, secondary_distance, next);
    tree_parent(tree, vec_get(tree->vertices, 0), NULL, parent);

    for(int i = 1; i < tree_size; i++) {
        int parent_i = graph_vertex_i(tree, parent[i]);
        if(next[parent_i] == graph_vertex_from_i(tree, i) && secondary_distance[parent_i] + 1 > primary_distance[i]) { 
            secondary_distance[i] = primary_distance[i];
            primary_distance[i] = secondary_distance[parent_i] + 1;
            next[i] = parent[i];
        } else if(next[parent_i] != graph_vertex_from_i(tree, i) && primary_distance[parent_i] + 1 > primary_distance[i]) {
            secondary_distance[i] = primary_distance[i];
            primary_distance[i] = primary_distance[parent_i] + 1;
            next[i] = parent[i];
        }
    }

    for(int i = 0; i < tree_size; i++) {
        longest_path[i] = primary_distance[i];
    }

    free(primary_distance);
    free(visited);
    free(secondary_distance);
    free(next);
    free(parent);
} 

int tree_diameter(struct graph* tree) {
    unsigned int tree_size = graph_vertices_len(tree);
    int* distance = malloc(sizeof(int) * tree_size);
    int* visited = malloc(sizeof(int) * tree_size);
    void** next = malloc(sizeof(void*) * tree_size);
    memset(distance, 0, tree_size * sizeof(int));
    memset(visited, 0, tree_size * sizeof(int));
    memset(next, 0, tree_size * sizeof(void*));

    tree_furthest_leaf_distance(tree, vec_get(tree->vertices, 0), distance, visited, NULL, NULL, next);
    int i = 0;
    while(distance[i] != 0) {
        i = graph_vertex_i(tree, next[i]);
    }

    memset(distance, 0, tree_size * sizeof(int));
    memset(visited, 0, tree_size * sizeof(int));
    memset(next, 0, tree_size * sizeof(void*));

    tree_furthest_leaf_distance(tree, vec_get(tree->vertices, i), distance, visited, NULL, NULL, next);
    int diameter = distance[i];

    free(distance);
    free(visited);
    free(next);

    return diameter;
}
// another method to calculate diameter is to calculate the maximum of `longest_path_through_vertex` for each vertex

void tree_ancestor_binary_lift_dfs(struct graph* tree, void* current, void* parent, int** ancestor, int* tin, int* tout, int t) {
    struct vertex* v = graph_vertex(tree, current);

    if(tin) tin[v->i] = ++t;

    ancestor[v->i][0] = graph_vertex_i(tree, parent);
    int l = log_2(graph_vertices_len(tree));
    for(int i = 1; i <= l; ++i) {
        ancestor[v->i][i] = ancestor[ancestor[v->i][i-1]][i-1];
    }

    for(int i = 0; i < vec_len(v->out); i++) {
        struct vertex* u = vec_get(v->out, i);
        if(u->value != parent) {
            tree_ancestor_binary_lift_dfs(tree, u->value, v->value, ancestor, tin, tout, t);
        }
    }

    if(tout) tout[v->i] = ++t;
}

int tree_vertex_is_ancestor(struct graph* tree, void* ancestor, void* descendant, int* tin, int* tout) {
    int u = graph_vertex_i(tree, ancestor);
    int v = graph_vertex_i(tree, descendant);
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void* tree_vertex_ancestor(struct graph* tree, void* current, int** ancestor, int k) {
    struct vertex* v = graph_vertex(tree, current);
    int kth_successor = k;
    while(k > 0) {
        kth_successor = ancestor[v->i][log_2(k)];
        k /= 2;
    }
    return vec_get(tree->vertices, kth_successor);
}

void* tree_lowest_common_ancestor_binary_lift(struct graph* tree, void* u, void* v, void* root) {
    unsigned int vertex_len = graph_vertices_len(tree);
    int** ancestor = malloc(vertex_len * sizeof(int*));
    for(int i = 0; i < vertex_len; i++) {
        ancestor[i] = malloc((log_2(vertex_len) + 1) * sizeof(int));
    }

    int tin[vertex_len];
    int tout[vertex_len];
    tree_ancestor_binary_lift_dfs(tree, root, root, ancestor, tin, tout, 0);

    if(tree_vertex_is_ancestor(tree, u, v, tin, tout)) return u;
    if(tree_vertex_is_ancestor(tree, v, u, tin, tout)) return v;
    int l = log_2(vertex_len);
    int j;
    for (int i = l; i >= 0; --i) {
        j = graph_vertex(tree, u)->i;
        if(!tree_vertex_is_ancestor(tree, vec_get(tree->vertices, ancestor[j][i]), v, tin, tout)) {
            u = vec_get(tree->vertices, ancestor[j][i]);
        }
    }

    j = graph_vertex(tree, u)->i;
    void* lca = vec_get(tree->vertices, ancestor[j][0]);

    for(int i = 0; i < vertex_len; i++) {
        free(ancestor[i]);
    }
    free(ancestor);

    return lca;
}

void tree_dfs_traversal_order(struct graph* tree, void* current, void* parent, int* visited, vector(void*) order) {
    struct vertex* s = graph_vertex(tree, current);
    if(visited[s->i]) return;
    visited[s->i] = 1;
    vec_push(order, current);

    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value == parent) continue;
        tree_dfs_traversal_order(tree, u->value, current, visited, order);
    }
}

void tree_euler_tour(struct graph* tree, void* current, void* parent, int h, int* depth, int* visited, vector(void*) euler_tour) {
    struct vertex* s = graph_vertex(tree, current);

    if(visited[s->i]) return;
    visited[s->i] = 1;

    vec_push(euler_tour, current);
    depth[s->i] = h;

    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value == parent) continue;
        tree_euler_tour(tree, u->value, current, h + 1, depth, visited, euler_tour);
        vec_push(euler_tour, current);
    }
}

void* tree_lowest_common_ancestor_farach_colton_and_bender(struct graph* tree, void* u, void* v, void* root) {
    unsigned int vertex_len = graph_vertices_len(tree);
    vector(void*) euler_tour = vec_new(void*);
    int visited[vertex_len];
    int depth[vertex_len];

    tree_euler_tour(tree, root, root, 1, depth, visited, euler_tour);

    
    vec_free(euler_tour, NULL);
}
