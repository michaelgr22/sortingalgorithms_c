#ifndef SORTEVALUATION_H_INCLUDED
#define SORTEVALUATION_H_INCLUDED

typedef double t_sortdata;
typedef void (*SortAlgorithm)(t_sortdata Data[], long DataCount);

static inline void swapdata(t_sortdata* A, t_sortdata* B)
{
    t_sortdata BufferTemp = *A;
    *A = *B;
    *B = BufferTemp;
}

t_sortdata* generateRandomData(long DataCount);
void printDataArray(t_sortdata Data[], long DataCount);

#endif // SORTEVALUATION_H_INCLUDED
