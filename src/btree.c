#include "../headers/btree.h"

BTree btree_new(int degree) {
    BTree btree;
    btree_init(&btree, degree);
    return btree;
}

int btree_init(BTree* btree, int degree) {
    struct btree_node* root = btree_node_new(1);
    btree->root = root;
    btree->degree = degree;
    return 0;
}

struct btree_node* btree_node_new(int is_leaf) {
    struct btree_node* node = malloc(sizeof(struct btree_node));
    btree_node_init(node, is_leaf);
    return node;
}

int btree_node_init(struct btree_node* node_ptr, int is_leaf) {
    vector(int) keys = vec_new(int);
    vector(struct btree_node*) children = vec_new(struct btree_node*);
    struct btree_node btree_node = { keys, children, is_leaf };
    *node_ptr = btree_node;
    return 0;
}

int btree_node_is_empty(struct btree_node* node) {
    return vec_len(node->keys) == 0;
}

int btree_node_is_full(struct btree_node* node, int degree) {
    return vec_len(node->keys) == 2 * degree - 1;
}

int btree_node_index_by_key(struct btree_node* node, int key) {
    int l = 0;
    int r = vec_len(node->keys) - 1;

    while(l <= r) {
        int m = (l + r)/2;
        if(vec_get(node->keys, m) < key) {
            l = m + 1; 
        } else if(vec_get(node->keys, m) > key) {
            r = m - 1;
        } else {
            return m;
        }
    }

    return l;
}

int btree_node_key_by_index(struct btree_node* node, int index) {
    return vec_get(node->keys, index);
}

struct btree_node* btree_node_child_after_key(struct btree_node* node, int key) {
    return vec_get(node->children, btree_node_index_by_key(node, key) + 1);
}

struct btree_node* btree_node_child_at_index(struct btree_node* node, int index) {
    return vec_get(node->children, index);
}

struct btree_node* btree_node_first_child(struct btree_node* node) {
    return vec_get(node->children, 0);
}

int btree_node_contains_key(struct btree_node* node, int key) {
    int index = btree_node_index_by_key(node, key);
    return btree_node_key_by_index(node, index) == key;
}

void btree_node_push_child(struct btree_node* node, struct btree_node* child_node) {
    vec_push(node->children, child_node);
}

void btree_node_insert_child(struct btree_node* node, int index, struct btree_node* child_node) {
    vec_insert(node->children, index, child_node);
}

void btree_node_insert_key(struct btree_node* node, int key) {
    vec_insert(node->keys, btree_node_index_by_key(node, key), key);
}

int btree_node_remove_key(struct btree_node* node, int key) {
    int index = btree_node_index_by_key(node, key);
    if(btree_node_key_by_index(node, index) != key) {
        return -1;
    }
    return vec_pop(node->keys, index);
}

void btree_node_split_children(struct btree_node* node, struct btree_node* split_node, int degree) {
    for(int i = 0; i < degree; i++) {
        btree_node_push_child(split_node, btree_node_child_at_index(node, i + degree));
    }
    for(int i = 0; i < degree; i++) {
        vec_pop(node->children, -1);
    }
}

int btree_node_split_keys(struct btree_node* node, struct btree_node* split_node, int degree) {
    int split_key = vec_get(node->keys, degree-1);
    for(int i = 0; i < degree-1; i++) {
        vec_push(split_node->keys, vec_get(node->keys, i + degree));
    }
    for(int i = 0; i < degree; i++) {
        vec_pop(node->keys, -1);
    }

    return split_key;
}

int btree_split_full_node(struct btree* btree, struct btree_node* node, struct btree_node* split_node) {
    int split_key = btree_node_split_keys(node, split_node, btree->degree);
    if(!node->is_leaf) {
        btree_node_split_children(node, split_node, btree->degree);
    }
    return split_key;
}

struct btree_node* btree_split_child(BTree* btree, struct btree_node* parent_node, int i) {
    struct btree_node* node = btree_node_child_at_index(parent_node, i);
    struct btree_node* split_node = btree_node_new(node->is_leaf);

    btree_node_insert_child(parent_node, i+1, split_node);

    int split_key = btree_split_full_node(btree, node, split_node);

    btree_node_insert_key(parent_node, split_key);

    return split_node;
}

struct btree_node* btree_search(BTree* btree, int key, struct btree_node* node) {
    if(node == NULL) {
        node = btree->root;
    }
    int i = btree_node_index_by_key(node, key);
    if(btree_node_contains_key(node, key)) {
        return node;
    } else if (node->is_leaf) {
        return NULL;
    } else {
        return btree_search(btree, key, btree_node_child_at_index(node, i));
    }
}


void btree_insert_into_non_full(BTree* btree, struct btree_node* node, int key) {
    if(node->is_leaf) {
        btree_node_insert_key(node, key);
        return;
    }

    int i = btree_node_index_by_key(node, key) + btree_node_contains_key(node, key);
    if(btree_node_is_full(btree_node_child_at_index(node, i), btree->degree)) {
        btree_split_child(btree, node, i);
        i += key > btree_node_key_by_index(node, i);
    }
    btree_insert_into_non_full(btree, btree_node_child_at_index(node, i), key);
}

void btree_insert(struct btree* btree, int key) {
    struct btree_node* root = btree->root;

    if(btree_node_is_full(root, btree->degree)) {
        struct btree_node* new_root = btree_node_new(0);
        btree->root = new_root;
        btree_node_insert_child(new_root, 0, root);

        btree_split_child(btree, new_root, 0);
        root = new_root;
    }

    btree_insert_into_non_full(btree, root, key);
}

int btree_delete_predecessor(BTree* btree, struct btree_node* node) {
    if(node->is_leaf) {
        return vec_pop(node->keys, -1);
    }
    int n = vec_len(node->keys) - 1;
    if(vec_len(vec_get(node->children, n)->keys) >= btree->degree) {
        btree_delete_sibling(btree, node, n + 1, n);
    } else {
        btree_delete_merge(btree, node, n, n + 1);
    }
    return btree_delete_predecessor(btree, vec_get(node->children, n));
}

int btree_delete_successor(BTree* btree, struct btree_node* node) {
    if(node->is_leaf) {
        return vec_pop(node->keys, 0);
    }
    if(vec_len(vec_get(node->children, 1)->keys) >= btree->degree) {
        btree_delete_sibling(btree, node, 0, 1);
    } else {
        btree_delete_merge(btree, node, 0, 1);
    }
    return btree_delete_successor(btree, vec_get(node->children, 0));
}

void btree_delete_merge(BTree* btree, struct btree_node* node, int i, int j) {
    struct btree_node* cnode = vec_get(node->children, i);
    struct btree_node* new;

    if(j > i) {
        struct btree_node* rsnode = vec_get(node->children, j);
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
        struct btree_node* lsnode = vec_get(node->children, j);
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
    struct btree_node* cnode = vec_get(node->children, i);
    if(i < j) {
        struct btree_node* rsnode = vec_get(node->children, j);
        vec_push(cnode->keys, vec_get(node->keys, i));
        vec_set(node->keys, i, vec_get(rsnode->keys, 0));
        if(vec_len(rsnode->children) > 0) {
            vec_push(cnode->children, vec_get(rsnode->children, 0));
            vec_zap(rsnode->children, 0, NULL);
        }
        vec_zap(rsnode->keys, 0, NULL);
    } else {
        struct btree_node* lsnode = vec_get(node->children, j);
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

    if(vec_len(vec_get(node->children, i)->keys) >= t) {
        vec_set(node->keys, i, btree_delete_predecessor(btree, vec_get(node->children, i)));
        return;
    } else if (vec_len(vec_get(node->children, i + 1)->keys) >= t) {
        vec_set(node->keys, i, btree_delete_successor(btree, vec_get(node->children, i + 1)));
        return;
    } else {
        btree_delete_merge(btree, node, i, i + 1);
        btree_delete_internal_node(btree, vec_get(node->children, i), key, btree->degree - 1);
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
    } else if(vec_len(vec_get(node->children, i)->keys) >= t) {
        btree_delete(btree, vec_get(node->children, i), key);
    } else {
        if(i != 0 && i + 2 < vec_len(node->children)) {
            if(vec_len(vec_get(node->children, i - 1)->keys) >= t) {
                btree_delete_sibling(btree, node, i, i - 1);
            } else if(vec_len(vec_get(node->children, i + 1)->keys) >= t) {
                btree_delete_sibling(btree, node, i, i + 1);
            } else {
                btree_delete_merge(btree, node, i, i + 1);
            }
        } else if(i == 0) {
            if(vec_len(vec_get(node->children, i + 1)->keys) >= t) {
                btree_delete_sibling(btree, node, i, i + 1);
            } else {
                btree_delete_merge(btree, node, i, i + 1);
            }
        } else if(i + 1 == vec_len(node->children)) {
            if(vec_len(vec_get(node->children, i - 1)->keys) >= t) {
                btree_delete_sibling(btree, node, i, i - 1);
            } else {
                btree_delete_merge(btree, node, i, i - 1);
            }
        }
        btree_delete(btree, vec_get(node->children, i), key);
    }
}

void btree_levelwise_traverse_and_print_keys(BTree* btree) {
    VecDeque(struct btree_node*) q = queue_new(struct btree_node*);
    VecDeque(int) levels = queue_new(int);
    queue_push_back(q, btree->root);
    queue_push_back(levels, 0);

    while(!queue_is_empty(q)) {
        struct btree_node* node = queue_pop_front(q);
        int level = queue_pop_front(levels);
        printf("level: %d: ", level);
        vec_print_primitive(node->keys, "%d");
        if(node->is_leaf) { continue; }
        for(int i = 0; i < vec_len(node->children); i++) {
            queue_push_back(q, vec_get(node->children, i));
            queue_push_back(levels, level+1);
        }
    }
    queue_free(q, NULL);
    queue_free(levels, NULL);
}
