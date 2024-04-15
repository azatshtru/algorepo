#include "../std/vector.c"
#include "../std/option.c"

stdOption(char)
stdVector(Optionchar)

stdVector(int)

//< left tile piece
//> right tile piece
//^ up tile piece
//V low tile piece
char Z[4] = { '<', '>', 'V', '^' };

int printRow(char* row, int X) {
    for(int i = 0; i < X; i++) { printf("%c", row[i]); }
    return 0;
}

int is_valid_row(char* row, int X, int Y, int numRows, Vector(Optionchar) * v, Vector(int)* vxi) {
    if(row[0]=='>') { return 0; }
    if(row[X-1]=='<') { return 0; }
    for(int i = 0; i < X; i++) {
        if(Y==0 && row[i]=='V') { return 0; }
        if(Y==numRows-1 && row[i]=='^') { return 0; }
    }
    if(Y==0) { return 1; }
    int flag = 0;
    int total = 0;
    for(int i = 0; i < (v[Y-1])->fill+1; i++) {
        total += *(vxi[Y-1]->array+i);
        for(int c = 0; c < X; c++) {
            //printf("character at old Y=%d : %c \n", Y-1, *((v[Y-1]->array+i)->some+c));
            if((*((v[Y-1]->array+i)->some+c) == '^' && row[c] != 'V') || (*((v[Y-1]->array+i)->some+c) != '^' && row[c] == 'V')) { 
                flag += *(vxi[Y-1]->array+i);
                break;
            }
        }
    }
    if(total==flag) { return 0; }
    return total-flag;
}

int constructRow(char* row, int X, int Y, int fill, int numRows, Vector(Optionchar) * v, Vector(int) * vxi) {
    for(int i = 0; i < 4; i++) {
        if(fill > 0 && row[fill-1]=='<' && Z[i]!='>') { continue; }
        if(fill > 0 && row[fill-1]!='<' && Z[i]=='>') { continue; }
        row[fill] = Z[i];
        if(fill==X-1) {
            char* fauxrow = (char*)malloc(sizeof(char)*X);
            for(int j = 0; j < X; j++) { fauxrow[j] = row[j]; }
            int p = is_valid_row(fauxrow, X, Y, numRows, v, vxi);
            if(p) {
                push(Optionchar, v[Y], Some(char, fauxrow));
                push(int, vxi[Y], p);
            }
            continue;
        }
        constructRow(row, X, Y, fill+1, numRows, v, vxi);
    }
    return 0;
}

int constructTileMatrix(int X, int Y) {
    Vector(Optionchar) * v = (Vector(Optionchar)*)malloc(sizeof(Vector(Optionchar))*Y);
    Vector(int) * vxi = (Vector(int)*)malloc(sizeof(Vector(int))*Y);
    for(int i = 0; i < Y; i++) { 
        v[i] = createVector(Optionchar);
        vxi[i] = createVector(int);
    }
    for(int y = 0; y < Y; y++) {
        char row[X];
        constructRow(row, X, y, 0, Y, v, vxi);
    }

    //for(int i = 0; i < Y; i++) {
        //printf("row %d: [ ", i+1);
        //for(int j = 0; j < v[i]->fill+1; j++) {
            //printRow((v[i]->array+j)->some, X);
            //printf(", ");
        //}
        //printf(" ]\n");
        //printf("row %d: [ ", i+1);
        //for(int j = 0; j < vxi[i]->fill+1; j++) {
            //printf("%d, ", *(vxi[i]->array+j));
        //}
        //printf(" ]\n");
    //}

    int sum = 0;
    for(int i = 0; i < vxi[Y-1]->fill+1; i++) { sum+=get(int, vxi[Y-1], i); }
    return sum;
}