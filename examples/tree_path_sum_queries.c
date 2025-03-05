#include "../headers/graph.h"
#include "../headers/logging.h"

// subtree sum query using a sparse segment tree
// serves as an example of subtree queries using DFS order array
// serves as an example of dynamic sparse segment tree

typedef struct tree_path_sum_query_sparse_segtree_vertex {
    int left_range;
    int right_range;
    int sum;
    int lazy;
    struct tree_path_sum_query_sparse_segtree_vertex* left;
    struct tree_path_sum_query_sparse_segtree_vertex* right;
} TreePathSumQuerySparseSegtree;

struct tree_path_sum_query_sparse_segtree_vertex* tree_path_sum_query_sparse_segtree_new(int left_range, int right_range) {
    struct tree_path_sum_query_sparse_segtree_vertex* v = malloc(sizeof(struct tree_path_sum_query_sparse_segtree_vertex));
    v->left_range = left_range;
    v->right_range = right_range;
    v->sum = 0;
    v->lazy = 0;
    v->left = NULL;
    v->right = NULL;
    return v;
}

void tree_path_sum_query_sparse_segtree_free(TreePathSumQuerySparseSegtree* v) {
    if(v == NULL) return;
    tree_path_sum_query_sparse_segtree_free(v->left);
    tree_path_sum_query_sparse_segtree_free(v->right);
    free(v);
}

void tree_path_sum_query_sparse_segtree_extend(struct tree_path_sum_query_sparse_segtree_vertex* v) {
    if (!v->left && v->left_range + 1 < v->right_range) {
        int t = (v->left_range + v->right_range) / 2;
        v->left = tree_path_sum_query_sparse_segtree_new(v->left_range, t);
        v->right = tree_path_sum_query_sparse_segtree_new(t, v->right_range);
    }
}

void tree_path_sum_query_sparse_segtree_add(struct tree_path_sum_query_sparse_segtree_vertex* v, int k, int x) {
    tree_path_sum_query_sparse_segtree_extend(v);
    v->sum += x;
    if (v->left) {
        if (k < v->left->right_range) {
            tree_path_sum_query_sparse_segtree_add(v->left, k, x);
        } else {
            tree_path_sum_query_sparse_segtree_add(v->right, k, x);
        }
    }
}

int tree_path_sum_query_sparse_segtree_sum(struct tree_path_sum_query_sparse_segtree_vertex* v, int l, int r) {
    if (l <= v->left_range && v->right_range <= r) return v->sum + (r - l) * v->lazy;
    int max = v->left_range > l ? v->left_range : l;
    int min = v->right_range < r ? v->right_range : r;
    if (max >= min) return 0;
    tree_path_sum_query_sparse_segtree_extend(v);
    v->sum += v->lazy * (v->right_range - v->left_range);
    v->right->lazy += v->lazy;
    v->left->lazy += v->lazy;
    v->lazy = 0;
    return tree_path_sum_query_sparse_segtree_sum(v->left, l, r) + tree_path_sum_query_sparse_segtree_sum(v->right, l, r);
}

void tree_path_sum_query_sparse_segtree_update_range(struct tree_path_sum_query_sparse_segtree_vertex* v, int l, int r, int x) {
    if (l <= v->left_range && v->right_range <= r) {
        v->lazy += x;
        return;
    }
    if(r < v->left_range || l > v->right_range) return;
    tree_path_sum_query_sparse_segtree_extend(v);
    int h = (v->right_range - v->left_range + r - l + r - v->right_range + l - v->left_range) / 2;
    v->sum += h * x;
    tree_path_sum_query_sparse_segtree_update_range(v->left, l, r, x);
    tree_path_sum_query_sparse_segtree_update_range(v->right, l, r, x);
}

int tree_path_sum_query_dfs_traversal_order(
    struct graph* tree, void* current, void* parent, int path_sum,
    int* visited, vector(void*) order, int* subtree_sizes, vector(int) path_sums
) {
    struct vertex* s = graph_vertex(tree, current);
    if(visited[s->i]) return subtree_sizes[s->i];
    visited[s->i] = 1;
    vec_push(order, current);
    vec_push(path_sums, path_sum);

    int subtree_size = 1;
    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* u = vec_get(s->out, i);
        if(u->value == parent) continue;
        subtree_size += tree_path_sum_query_dfs_traversal_order(tree, u->value, current, *(int*)u->value + path_sum, visited, order, subtree_sizes, path_sums);
    }

    subtree_sizes[s->i] = subtree_size;
    return subtree_size;
}

TreePathSumQuerySparseSegtree* tree_path_sum_segment_tree_construct(struct graph* tree, void* root, int* subtree_sizes, int* order_map) {
    unsigned int vertex_len = graph_vertices_len(tree);
    int visited[vertex_len];
    memzero(visited, vertex_len * sizeof(int));
    memzero(subtree_sizes, vertex_len * sizeof(int));
    vector(int) path_sums = vec_new(int);
    vector(void*) order = vec_new(void*);

    tree_path_sum_query_dfs_traversal_order(tree, root, root, *(int*)root, visited, order, subtree_sizes, path_sums);

    TreePathSumQuerySparseSegtree* segtree = tree_path_sum_query_sparse_segtree_new(0, 1<<(log_2(vertex_len)+1));
    for(int i = 0; i < vertex_len; i++) {
        tree_path_sum_query_sparse_segtree_add(segtree, i, (vec_get(path_sums, i)));
        order_map[graph_vertex_i(tree, vec_get(order, i))] = i;
    }

    vec_free(path_sums, NULL);
    vec_free(order, NULL);

    return segtree;
}

int tree_path_sum(struct graph* tree, TreePathSumQuerySparseSegtree* segtree, int* order, int* subtree_sizes, void* v) {
    struct vertex* s = graph_vertex(tree, v);
    return tree_path_sum_query_sparse_segtree_sum(segtree, order[s->i], order[s->i] + 1);
}

void tree_path_sum_query_add_vertex_value(struct graph* tree, TreePathSumQuerySparseSegtree* segtree, int* order, int* subtree_sizes, void* v, int value) {
    struct vertex* s = graph_vertex(tree, v);
    tree_path_sum_query_sparse_segtree_update_range(segtree, order[s->i], order[s->i] + subtree_sizes[s->i], value);
}

int main() {
    int things[9] = { 4, 5, 3, 5, 2, 3, 5, 3, 1 };
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

    int subtree_sizes[9];
    int order[9];
    TreePathSumQuerySparseSegtree* segtree = tree_path_sum_segment_tree_construct(&tree, things + 0, subtree_sizes, order);

    graph_free(&tree);
}
