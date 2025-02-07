#ifndef HUFFMAN_CODING
#define HUFFMAN_CODING

#include "priority_queue.h"
#include "miniqutils.h"

#define HUFFMAN_ENCODING_TABLE_SIZE 128

struct huffman_prefix_table {
    int table[HUFFMAN_ENCODING_TABLE_SIZE];
};

struct huffman_tree_node {
    char symbol;
    int is_leaf;
    int frequency;

    struct huffman_tree_node* left;
    struct huffman_tree_node* right;
};

struct huffman_tree_node* huffman_tree_node_new(char symbol, int is_leaf, int frequency, struct huffman_tree_node* left, struct huffman_tree_node* right);
void huffman_tree_node_free(struct huffman_tree_node* node);

int huffman_tree_node_priority(void* node);

struct huffman_tree_node* huffman_tree(char* cstr, int len);

void huffman_encoding_prefix_codes(struct huffman_prefix_table* prefix_table, struct huffman_tree_node* node, int code);
void huffman_encoding(struct huffman_prefix_table* prefix_table, char* cstr, int len);

#endif
