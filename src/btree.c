#include "../headers/btree.h"

BTree btree_new(int degree) {
    BTree btree;
    btree_init(&btree, degree);
    return btree;
}

int btree_init(BTree* btree, int degree) {
    struct btree_node* root = malloc(sizeof(struct btree_node));
    btree_node_init(root, 1);
    btree->root = root;
    btree->degree = degree;
    return 0;
}

int btree_node_init(struct btree_node* node_ptr, int is_leaf) {
    vector(int) keys = vec_new(int);
    vector(struct btree_node) children = vec_new(struct btree_node);
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

void btree_split_child(BTree* btree, struct btree_node* parent_node, int i) {
    int t = btree->degree;
    // get the full child of parent node.
    struct btree_node* node = *parent_node->children + i;

    // create a new split_node and add it to parent's list of children.
    struct btree_node split_node;
    btree_node_init(&split_node, node->is_leaf);
    vec_insert(parent_node->children, i+1, split_node);

    // insert the median of the full child node into parent node
    vec_insert(parent_node->keys, i, vec_get(node->keys, t-1));

    // split apart child node's keys into itself & split_node
    for(int j = t; j < 2*t-1; j++) {
        vec_push(split_node.keys, vec_get(node->keys, j)); 
    }
    for(int j = 0; j < t; j++) {
        vec_zap(node->keys, -1, NULL); 
    }
    // vec_resize((Vector*)split_node.keys, t-1);
    // memcpy(split_node.keys, *(node->keys), t-1 * ((Vector*)split_node.keys)->type_size);
    //
    // vec_resize((Vector*)node->keys, t-1);


    // if child is not a leaf, we reassign child's children to itself & split_node.
    if(!node->is_leaf) {
        for(int j = t; j < 2*t; j++) {
            vec_push(split_node.children, vec_get(node->children, j)); 
        }
        for(int j = 0; j < t+1; j++) {
            vec_zap(node->children, -1, NULL); 
        }
    }
}

void btree_shush_insert(BTree* btree, struct btree_node* node, int key) {
    int t = btree->degree;
    int i = vec_len(node->keys) - 1;

    if(node->is_leaf) {
        vec_push(node->keys, -1);
        while(i >= 0 && key < vec_get(node->keys, i)) {
            vec_set(node->keys, i+1, vec_get(node->keys, i));
            --i;
        }
        vec_set(node->keys, i+1, key);
    } else {
        while(i >= 0 && key < vec_get(node->keys, i)) { --i; }
        i++;
        if(vec_len(vec_get(node->children, i).keys) == 2*t-1) {
            btree_split_child(btree, node, i);
            if(key > vec_get(node->keys, i)) {
                i++;
            }
        }
        btree_shush_insert(btree, *node->children + i, key);
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

int btree_delete_predecessor(BTree* btree, struct btree_node* node) {
    if(node->is_leaf) {
        return vec_pop(node->keys, -1);
    }
    int n = vec_len(node->keys) - 1;
    if(vec_len(vec_get(node->children, n).keys) >= btree->degree) {
        btree_delete_sibling(btree, node, n + 1, n);
    } else {
        btree_delete_merge(btree, node, n, n + 1);
    }
    return btree_delete_predecessor(btree, *node->children + n);
}

int btree_delete_successor(BTree* btree, struct btree_node* node) {
    if(node->is_leaf) {
        return vec_pop(node->keys, 0);
    }
    if(vec_len(vec_get(node->children, 1).keys) >= btree->degree) {
        btree_delete_sibling(btree, node, 0, 1);
    } else {
        btree_delete_merge(btree, node, 0, 1);
    }
    return btree_delete_successor(btree, *node->children + 0);
}

void btree_delete_merge(BTree* btree, struct btree_node* node, int i, int j) {
    struct btree_node* cnode = *node->children + i;
    struct btree_node* new;

    if(j > i) {
        struct btree_node* rsnode = *node->children + j;
        vec_push(cnode->keys, vec_get(node->keys, i));
        for(int k = 0; k < vec_len(rsnode->keys); k++) {
            vec_push(cnode->keys, vec_get(rsnode->keys, k));
            if(vec_len(rsnode->children) > 0) {
                vec_push(cnode->children, vec_get(rsnode->children, k));
            }
        }
        if(vec_len(rsnode->children) > 0) {
            vec_push(cnode->children, vec_pop(rsnode->children, -1));
        }
        new = cnode;
        vec_zap(node->keys, i, NULL);
        vec_zap(node->children, j, NULL);
    } else {
        struct btree_node* lsnode = *node->children + j;
        vec_push(lsnode->keys, vec_get(node->keys, j));
        for(int k = 0; k < vec_len(cnode->keys); k++) {
            vec_push(lsnode->keys, vec_get(cnode->keys, i));
            if(vec_len(lsnode->children) > 0) {
                vec_push(lsnode->children, vec_get(cnode->children, i));
            }
        }
        if(vec_len(lsnode->children) > 0) {
            vec_push(lsnode->children, vec_pop(cnode->children, -1));
        }
        new = lsnode;
        vec_zap(node->keys, j, NULL);
        vec_zap(node->children, i, NULL);
    }

    if(node == btree->root && vec_len(node->keys) == 0) {
        btree->root = new;
    }
}

void btree_delete_sibling(BTree* btree, struct btree_node* node, int i, int j) {
    struct btree_node* cnode = *node->children + i;
    if(i < j) {
        struct btree_node* rsnode = *node->children + j;
        vec_push(cnode->keys, vec_get(node->keys, i));
        vec_set(node->keys, i, vec_get(rsnode->keys, 0));
        if(vec_len(rsnode->children) > 0) {
            vec_push(cnode->children, vec_get(rsnode->children, 0));
            vec_zap(rsnode->children, 0, NULL);
        }
        vec_zap(rsnode->keys, 0, NULL);
    } else {
        struct btree_node* lsnode = *node->children + j;
        vec_insert(cnode->keys, 0, vec_get(node->keys, i - 1));
        vec_set(node->keys, i - 1, vec_pop(lsnode->keys, -1));
        if(vec_len(lsnode->children) > 0) {
            vec_insert(cnode->children, 0, vec_pop(lsnode->children, -1));
        }
    }
}

void btree_delete_internal_node(BTree* btree, struct btree_node* node, int key, int i) {
    int t = btree->degree;
    if(node->is_leaf) {
        if(vec_get(node->keys, i) == key) {
            vec_zap(node->keys, i, NULL);
        }
        return;
    }

    if(vec_len(vec_get(node->children, i).keys) >= t) {
        vec_set(node->keys, i, btree_delete_predecessor(btree, *node->children + i));
        return;
    } else if (vec_len(vec_get(node->children, i + 1).keys) >= t) {
        vec_set(node->keys, i, btree_delete_successor(btree, *node->children + i + 1));
        return;
    } else {
        btree_delete_merge(btree, node, i, i + 1);
        btree_delete_internal_node(btree, *node->children + i, key, btree->degree - 1);
    }
}

void btree_delete(BTree* btree, struct btree_node* node, int key) {
    int t = btree->degree; 
    int i = 0;
    
    while(i < vec_len(node->keys) && key > vec_get(node->keys, i)) {
        i++;
        if(node->is_leaf) {
            if(i < vec_len(node->keys) && key == vec_get(node->keys, i)) {
                vec_zap(node->keys, i, NULL);
            }
            return;
        }
    }
    if(i < vec_len(node->keys) && vec_get(node->keys, i) == key) {
        return btree_delete_internal_node(btree, node, key, i);
    } else if(vec_len(vec_get(node->children, i).keys) >= t) {
        btree_delete(btree, *node->children + i, key);
    } else {
        if(i != 0 && i + 2 < vec_len(node->children)) {
            if(vec_len(vec_get(node->children, i - 1).keys) >= t) {
                btree_delete_sibling(btree, node, i, i - 1);
            } else if(vec_len(vec_get(node->children, i + 1).keys) >= t) {
                btree_delete_sibling(btree, node, i, i + 1);
            } else {
                btree_delete_merge(btree, node, i, i + 1);
            }
        } else if(i == 0) {
            if(vec_len(vec_get(node->children, i + 1).keys) >= t) {
                btree_delete_sibling(btree, node, i, i + 1);
            } else {
                btree_delete_merge(btree, node, i, i + 1);
            }
        } else if(i + 1 == vec_len(node->children)) {
            if(vec_len(vec_get(node->children, i - 1).keys) >= t) {
                btree_delete_sibling(btree, node, i, i - 1);
            } else {
                btree_delete_merge(btree, node, i, i - 1);
            }
        }
        btree_delete(btree, node->children[i], key);
    }
}
