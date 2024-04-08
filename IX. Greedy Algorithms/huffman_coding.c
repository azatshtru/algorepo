#include "../std/vector.c"
#include "../std/box.c"

typedef struct huffman_node {
    char c;
    int freq;

    struct huffman_node* l;
    struct huffman_node* r;
} HuffmanNode;

stdBox(HuffmanNode)
stdVector(BoxHuffmanNode)

//To compress a string, it is worthwhile to assign shorter bitcode for characters that appear often.
//The bitcode for each characters should not be a prefix for any other character so that the entire string can be generated.
//One such algorithm to achieve the above two properties in the compression is Huffman coding.

HuffmanNode make_HuffmanNode(char c, int freq) {
    HuffmanNode n = { c, freq, NULL, NULL };
    return n;
}

Vector(BoxHuffmanNode) buildFrequencyVector(char* S) {
    int length = '~' - ' ';
    int* frequency = (int*)malloc(sizeof(int)*length);
    for(int i = 0; i < length; i++) { *(frequency+i) = 0; }
    char* c = S;
    while(*c != '\0') { *(frequency + (int)(*c++) - 32) += 1; }
    Vector(BoxHuffmanNode) v = createVector(BoxHuffmanNode);
    for(int i = 0; i < length; i++) { 
        if(*(frequency+i)){ push(BoxHuffmanNode, v, Box(HuffmanNode, make_HuffmanNode((char)(i+32), *(frequency+i)))); }
    }
    return v;
}

int cmpHuffmanNode(BoxHuffmanNode a, BoxHuffmanNode b) { return a.value->freq>b.value->freq; }

char buffer[20];
int count = -1;
int dfsHuffmanTree(HuffmanNode n) {
    count += 1;
    if(n.c == '\n'){
        buffer[count] = '0';
        dfsHuffmanTree(*(n.r));
        buffer[count] = '1';
        dfsHuffmanTree(*(n.l));
    } else {
        printf("%s", buffer);
        printf(" %c\n", n.c);
    }
    count -= 1;
    return 0;
}

int buildHuffmanTree(char* S) {
    Vector(BoxHuffmanNode) v = buildFrequencyVector(S);
    quick_sort(BoxHuffmanNode, v, 0, v->fill, cmpHuffmanNode);
    while(v->fill > 0) {
        HuffmanNode p = make_HuffmanNode('\n', get(BoxHuffmanNode, v, v->fill-1).value->freq + get(BoxHuffmanNode, v, v->fill).value->freq);
        BoxHuffmanNode h = pop(BoxHuffmanNode, v, v->fill);
        if(h.value->c == '\n') { 
            p.l = h.value;
            p.r = pop(BoxHuffmanNode, v, v->fill).value;
        } else {
            p.r = h.value;
            p.l = pop(BoxHuffmanNode, v, v->fill).value;
        }
        push(BoxHuffmanNode, v, Box(HuffmanNode, p));
        int k = v->fill;
        while(get(BoxHuffmanNode, v, (k-1)/2).value->freq < p.freq) {
            *(v->array + k) = get(BoxHuffmanNode, v, (k-1)/2);
            *(v->array + (k-1)/2) = Box(HuffmanNode, p);
            k = (k-1)/2;
            if(k < 0) { break; }
        }
    }
    printf("\n");
    dfsHuffmanTree(*(get(BoxHuffmanNode, v, 0).value));

    return 0;
}