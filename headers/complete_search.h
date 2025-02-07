#include "miniqutils.h"
#include "vector.h"

#ifndef COMPLETE_SEARCH
#define COMPLETE_SEARCH

typedef struct subset_iterator {
    vector(int) state;
    int n;
} SubsetIterator;

void subset_init(SubsetIterator* it);
SubsetIterator subset_next(SubsetIterator it, int n);

#endif
