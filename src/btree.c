#include "../headers/btree.h"

BTree btree_new(int degree) {
    BTree btree;
    btree_init(&btree, degree);
    return btree;
}

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
    // y is a full child of x
    struct btree_node* y = *x->children + i;

    // create a new node and add it to x's list of children
    struct btree_node z;
    btree_node_init(&z, y->is_leaf);
    vec_insert(x->children, i+1, z);


    // insert the median of the full child y into x
    vec_insert(x->keys, i, vec_get(y->keys, t-1));

    // vec_resize((Vector*)z.keys, t-1);
    // memcpy(z.keys, *(y->keys), t-1 * ((Vector*)z.keys)->type_size);
    //
    // vec_resize((Vector*)y->keys, t-1);

    // split apart y's keys into y & z
    for(int j = t; j < 2*t-1; j++) {
        vec_push(z.keys, vec_get(y->keys, j)); 
    }
    for(int j = 0; j < t; j++) {
        vec_zap(y->keys, -1, NULL); 
    }

    // if y is not a leaf, we reassign y's children to y & z
    if(!y->is_leaf) {
        for(int j = t; j < 2*t; j++) {
            vec_push(z.children, vec_get(y->children, j)); 
        }
        for(int j = 0; j < t+1; j++) {
            vec_zap(y->children, -1, NULL); 
        }
    }
}

void btree_shush_insert(BTree* btree, struct btree_node* x, int key) {
    int t = btree->degree;
    int i = vec_len(x->keys) - 1;

    if(x->is_leaf) {
        vec_push(x->keys, -1);
        while(i >= 0 && key < vec_get(x->keys, i)) {
            vec_set(x->keys, i+1, vec_get(x->keys, i));
            --i;
        }
        vec_set(x->keys, i+1, key);
    } else {
        while(i >= 0 && key < vec_get(x->keys, i)) { --i; }
        i++;
        if(vec_len(vec_get(x->children, i).keys) == 2*t-1) {
            btree_split_child(btree, x, i);
            if(key > vec_get(x->keys, i)) {
                i++;
            }
        }
        btree_shush_insert(btree, *x->children + i, key);
    }
}

void btree_insert(struct btree* btree, int key) {
    int t = btree->degree;
    struct btree_node* root = btree->root;

    if(vec_len(root->keys) == 2*t-1) {
        struct btree_node* new_root = malloc(sizeof(struct btree_node));

        btree_node_init(new_root, 0);
        btree->root = new_root;

        vec_insert(new_root->children, 0, *root);

        btree_split_child(btree, new_root, 0);
        btree_shush_insert(btree, new_root, key);
    } else {
        btree_shush_insert(btree, root, key);
    }
}
