#include "../headers/graph.h"
#include "../headers/logging.h"

// subtree sum query using a sparse segment tree
// serves as an example of subtree queries using DFS order array
// serves as an example of dynamic sparse segment tree

typedef struct subtree_sum_query_sparse_segtree_vertex {
    int left_range;
    int right_range;
    int sum;
    struct subtree_sum_query_sparse_segtree_vertex* left;
    struct subtree_sum_query_sparse_segtree_vertex* right;
} SubtreeSumQuerySparseSegtree;

struct subtree_sum_query_sparse_segtree_vertex* subtree_sum_query_sparse_segtree_new(int left_range, int right_range) {
    struct subtree_sum_query_sparse_segtree_vertex* v = malloc(sizeof(struct subtree_sum_query_sparse_segtree_vertex));
    v->left_range = left_range;
    v->right_range = right_range;
    v->sum = 0;
    v->left = NULL;
    v->right = NULL;
    return v;
}

void subtree_sum_query_sparse_segtree_free(SubtreeSumQuerySparseSegtree* v) {
    if(v == NULL) return;
    subtree_sum_query_sparse_segtree_free(v->left);
    subtree_sum_query_sparse_segtree_free(v->right);
    free(v);
}

void subtree_sum_query_sparse_segtree_extend(struct subtree_sum_query_sparse_segtree_vertex* v) {
    if (!v->left && v->left_range + 1 < v->right_range) {
        int t = (v->left_range + v->right_range) / 2;
        v->left = subtree_sum_query_sparse_segtree_new(v->left_range, t);
        v->right = subtree_sum_query_sparse_segtree_new(t, v->right_range);
    }
}

void subtree_sum_query_sparse_segtree_add(struct subtree_sum_query_sparse_segtree_vertex* v, int k, int x) {
    subtree_sum_query_sparse_segtree_extend(v);
    v->sum += x;
    if (v->left) {
        if (k < v->left->right_range) {
            subtree_sum_query_sparse_segtree_add(v->left, k, x);
        } else {
            subtree_sum_query_sparse_segtree_add(v->right, k, x);
        }
    }
}

int subtree_sum_query_sparse_segtree_sum(struct subtree_sum_query_sparse_segtree_vertex* v, int l, int r) {
    if (l <= v->left_range && v->right_range <= r)
        return v->sum;
    int max = v->left_range > l ? v->left_range : l;
    int min = v->right_range < r ? v->right_range : r;
    if (max >= min)
        return 0;
    subtree_sum_query_sparse_segtree_extend(v);
    return subtree_sum_query_sparse_segtree_sum(v->left, l, r) + subtree_sum_query_sparse_segtree_sum(v->right, l, r);
}

int subtree_sum_query_dfs_traversal_order(struct graph* tree, void* current, void* parent, int* visited, vector(void*) order, int* subtree_sizes) {
    struct vertex* s = graph_vertex(tree, current);
    if(visited[s->i]) return subtree_sizes[s->i];
    visited[s->i] = 1;
    vec_push(order, current);

    int subtree_size = 1;
    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value == parent) continue;
        subtree_size += subtree_sum_query_dfs_traversal_order(tree, u->value, current, visited, order, subtree_sizes);
    }

    subtree_sizes[s->i] = subtree_size;
    return subtree_size;
}

int subtree_sum(struct graph* tree, void* root, int query_len, int* out) {
    unsigned int vertex_len = graph_vertices_len(tree);
    int visited[vertex_len];
    memzero(visited, vertex_len * sizeof(int));
    int subtree_sizes[vertex_len];
    memzero(subtree_sizes, vertex_len * sizeof(int));
    vector(void*) order = vec_new(void*);

    subtree_sum_query_dfs_traversal_order(tree, root, root, visited, order, subtree_sizes);

    SubtreeSumQuerySparseSegtree* segtree = subtree_sum_query_sparse_segtree_new(0, 16);
    for(int i = 0; i < vertex_len; i++) {
        subtree_sum_query_sparse_segtree_add(segtree, i, *(int*)(vec_get(order, i)));
    }

    for(int i = 0; i < vertex_len; i++) {
        int index = graph_vertex_i(tree, vec_get(order, i));
        out[index] = subtree_sum_query_sparse_segtree_sum(segtree, i, i + subtree_sizes[index]);
    }

    vec_free(order, NULL);
    return 0;
}

int main() {
    int things[9] = { 2, 3, 5, 3, 1, 4, 4, 3, 1 };
    struct graph tree = graph_new();
    for(int i = 0; i < 9; i++) {
        graph_add_vertex(&tree, things + i);
    }
    graph_add_edge_symmetric(&tree, things + 0, things + 1, 1);
    graph_add_edge_symmetric(&tree, things + 0, things + 2, 1);
    graph_add_edge_symmetric(&tree, things + 0, things + 3, 1);
    graph_add_edge_symmetric(&tree, things + 0, things + 4, 1);
    graph_add_edge_symmetric(&tree, things + 1, things + 5, 1);
    graph_add_edge_symmetric(&tree, things + 3, things + 6, 1);
    graph_add_edge_symmetric(&tree, things + 3, things + 7, 1);
    graph_add_edge_symmetric(&tree, things + 3, things + 8, 1);

    int out[9];
    subtree_sum(&tree, things + 0, 3, out);
    log_array(out, int, 9, x, printf("%d", x));

    graph_free(&tree);
}
