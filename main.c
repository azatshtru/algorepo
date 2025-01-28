#include <stdio.h>
#include "headers/huffman_coding.h"

int main() {
    struct huffman_prefix_table table;
    huffman_encoding(&table, "A DEAD DAD CEDED A BAD BABE A BEADED ABACA BED", 46);
    return 0;
}
