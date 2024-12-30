#include "../headers/btree.h"
#include <string.h>

typedef struct btree BTree;

int btree_init(BTree* btree, int degree) {
    struct btree_node* root = malloc(sizeof(struct btree_node));
    btree_node_init(root, 0);
    btree->root = root;
    btree->degree = degree;
    return 0;
}

int btree_node_init(struct btree_node* node_ptr, int is_leaf) {
    vector(int) keys = vec_new(int);
    vector(struct btree_node) children = is_leaf ? NULL : vec_new(struct btree_node);
    struct btree_node btree_node = { keys, children, is_leaf };
    *node_ptr = btree_node;
    return 0;
}

struct btree_node* btree_search(BTree btree, int key, struct btree_node* node) {
    if(node == NULL) {
        node = btree.root;
    }
    int i = 0;
    while(i < vec_len(node->keys) && key > vec_get(node->keys, i)) { i++; }
    if(i < vec_len(node->keys) && key == vec_get(node->keys, i)) {
        return node;
    } else if (node->is_leaf) {
        return NULL;
    } else {
        return btree_search(btree, key, *node->children + i);
    }
}

void btree_split_child(BTree* btree, struct btree_node* x, int i) {
    int t = btree->degree;
    struct btree_node* y = *x->children + i;

    struct btree_node z;
    btree_node_init(&z, y->is_leaf);
    vec_insert(x->children, i+1, z);

    vec_insert(x->keys, i, vec_get(y->keys, t-1));

    // vec_resize((Vector*)z.keys, t-1);
    // memcpy(z.keys, *(y->keys), t-1 * ((Vector*)z.keys)->type_size);
    //
    // vec_resize((Vector*)y->keys, t-1);

    for(int j = t; j < 2*t-1; j++) {
        vec_push(z.keys, vec_get(y->keys, j)); 
    }
    for(int j = 0; j < t; j++) {
        vec_zap(y->keys, -1, NULL); 
    }

    if(!y->is_leaf) {
        for(int j = t; j < 2*t; j++) {
            vec_push(z.children, vec_get(y->children, j)); 
        }
        for(int j = 0; j < t+1; j++) {
            vec_zap(y->children, -1, NULL); 
        }
    }
}
