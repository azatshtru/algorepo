#include "../headers/huffman_coding.h"
#include <stdio.h>

int huffman_tree_node_priority(void* node_ptr) {
    struct huffman_tree_node* node = *((struct huffman_tree_node**)node_ptr);
    return node->frequency;
}

struct huffman_tree_node* huffman_tree_node_new(char symbol, int is_leaf, int frequency, struct huffman_tree_node* left, struct huffman_tree_node* right) {
    struct huffman_tree_node* node = malloc(sizeof(struct huffman_tree_node));
    node->symbol = symbol;
    node->is_leaf = is_leaf;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

void huffman_tree_node_free(struct huffman_tree_node* node) {
    free(node);
}

struct huffman_tree_node* huffman_tree(char* cstr, int len) {
    struct huffman_tree_node nodes[HUFFMAN_ENCODING_TABLE_SIZE];
    memset(nodes, 0, HUFFMAN_ENCODING_TABLE_SIZE * sizeof(struct huffman_tree_node));

    for(int i = 0; i < len; i++) {
        nodes[cstr[i]].frequency++;
        nodes[cstr[i]].symbol = cstr[i];
    }

    PriorityQueue(struct huffman_tree_node*) tree = priority_queue_new(struct huffman_tree_node*);

    for(int i = 1; i < HUFFMAN_ENCODING_TABLE_SIZE; i++) {
        if(nodes[i].frequency > 0) {
            struct huffman_tree_node* leaf = huffman_tree_node_new(i, 1, nodes[i].frequency, NULL, NULL);
            priority_queue_nq(tree, leaf, nodes[i].frequency);
        }
    }

    while(priority_queue_len(tree) > 1) {
        struct huffman_tree_node* left = priority_queue_dq(tree);
        struct huffman_tree_node* right = priority_queue_dq(tree);
        struct huffman_tree_node* internal = huffman_tree_node_new(0, 0, left->frequency + right->frequency, left, right);
        priority_queue_nq(tree, internal, left->frequency + right->frequency);
    }

    struct huffman_tree_node* root = priority_queue_dq(tree);

    priority_queue_free(tree, NULL);
    
    return root;
}


void huffman_encoding_prefix_codes(struct huffman_prefix_table* prefix_table, struct huffman_tree_node* node, int code) {
    if(node == NULL) {
        return;
    }
    
    if(node->is_leaf) {
        prefix_table->table[node->symbol] = code;
    }

    huffman_encoding_prefix_codes(prefix_table, node->left, code<<1 | 0);
    huffman_encoding_prefix_codes(prefix_table, node->right, code<<1 | 1);
    free(node->left);
    free(node->right);
}

void huffman_encoding(struct huffman_prefix_table* prefix_table, char* cstr, int len) {
    struct huffman_tree_node* root = huffman_tree(cstr, len);
    huffman_encoding_prefix_codes(prefix_table, root, 0);
    free(root);
}
