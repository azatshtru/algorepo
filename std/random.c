typedef unsigned int uint;

uint f_randi(uint index) {
    index=(index<<13)^index;
    return (index * (index*index*15731+789221)+1376312589)&0x7fffffff;
}