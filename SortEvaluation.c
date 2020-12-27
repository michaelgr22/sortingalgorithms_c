#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SortEvaluation.h"

t_sortdata* generateRandomData(long DataCount)
{
    t_sortdata* ItemStorage;
    ItemStorage = (t_sortdata*)malloc(DataCount * sizeof(t_sortdata));
    for (int i=0; i<DataCount; i++)
    {
        ItemStorage[i]=(double)rand()/rand();
    }
    return ItemStorage;
}

void printDataArray(t_sortdata Data[], long DataCount)
{
    printf("\n---------Anfang---------\n");
    for (int i=0; i<DataCount; i++)
    {
        printf("%f, ", Data[i]);
        if (!((i+1)%5))
        {
            printf("\n");
        }
    }
    printf("\n----------Ende----------\n");
}
