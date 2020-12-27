#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SortEvaluation.h"
#include "MeasureTime.h"

void Bubblesort(t_sortdata data[], long datacount)
{
    bool datachanged;
    do
    {
        datachanged=false;
        for(int i=0; i<datacount-1; i++)
        {
            if (data[i]>data[i+1])
            {
                /* Swap Items */
                swapdata(&data[i], &data[i+1]);
                datachanged=true;
            }
        }
    }
    while (datachanged);
}

void Shakersort(t_sortdata data[], long datacount)
{
    bool datachanged;
    int start = -1;
    int end = datacount-2;
    do
    {
        datachanged = false;
        start++;
        for(int i=0; i<=end; i++)
        {
            if (data[i]>data[i+1])
            {
                /* Swap Items */
                swapdata(&data[i], &data[i+1]);
                datachanged=true;
            }
        }
        if(!datachanged)
        {
            break;
        }
        datachanged = false;
        end--;
        for(int i=end; i>start; i--)
        {
            if (data[i]>data[i+1])
            {
                /* Swap Items */
                swapdata(&data[i], &data[i+1]);
                datachanged=true;
            }
        }

    }
    while(datachanged);
}

t_sortdata getPivot(t_sortdata data[], long datacount)
{
    double sum=0;

    for(int i=0; i<datacount; i++)
    {
        sum+=data[i];
    }
    return (t_sortdata)sum/datacount;
}

void Quicksort(t_sortdata data[], long datacount)
{
    if(datacount < 2)
    {
        return;
    }

    if(datacount == 2)
    {
        if(data[0] > data[1])
        {
            swapdata(&data[0], &data[1]);
            return;
        }
        else
        {
            return;
        }
    }

    int left=0;
    int right=datacount-1;
    t_sortdata pivot = getPivot(data, datacount);

    while(left < right)
    {
        while(left < right && data[left] < pivot)
        {
            left++;
        }

        while(right > left && data[right] >= pivot)
        {
            right--;
        }

        if(left < right)
        {
            swapdata(&data[left], &data[right]);
        }
    }
    int seperateelement=right;
    if(seperateelement==0)
    {
        seperateelement++;
    }

    Quicksort(data, seperateelement);
    Quicksort(&data[seperateelement], datacount-seperateelement);

}

void Selectionsort(t_sortdata data[], long datacount)
{
    int start=0;
    while(start<datacount)
    {
        int minposition=start;

        for(int i=start; i<datacount; i++)
        {
            if(data[i]<data[minposition])
            {
                minposition=i;
            }
        }
        swapdata(&data[minposition], &data[start]);
        start++;
    }
}

void Insertionsort(t_sortdata data[], long datacount)
{
    for(int i=1; i<datacount; i++)
    {
        t_sortdata tosort = data[i];
        int j=i;
        while(j>0 && data[j-1] > tosort)
        {
            data[j] = data[j-1];
            j--;
        }
        data[j] = tosort;
    }
}

void measureAlgorithm(SortAlgorithm algorithm, long dataamount, t_timevalue* sortduration, t_timevalue* sortdurationpresorted)
{
    t_stopwatch mywatch;
    t_sortdata* sampledata;
    sampledata = generateRandomData(dataamount);

    //unsorted data
    startStopwatch(&mywatch);
    algorithm(sampledata, dataamount);
    *sortduration=stopStopwatch(&mywatch);

    //change first and last
    swapdata(&sampledata[dataamount-1], &sampledata[0]);

    //sorted data
    startStopwatch(&mywatch);
    algorithm(sampledata, dataamount);
    *sortdurationpresorted=stopStopwatch(&mywatch);

    free(sampledata);
}


int main()
{
    srand(time(NULL));

    /* Numer of data items to be used in sorting */
    long experimentsize[]={100,200,500,1000,2000,5000, 7000,10000,20000,30000,40000,50000,60000,70000};
    int numberofexperiments=sizeof(experimentsize)/sizeof(long);

    /* Array of names of Algorithms for display purposes */
    char algorithmname[][20]= {"Bubblesort", "Shakersort", "Quicksort", "Selectionsort", "Insertionsort"};

    /* Array of sorting functions implementing various algorithms */
    SortAlgorithm myalgorithms[]= {Bubblesort, Shakersort, Quicksort, Selectionsort, Insertionsort};

    /* Calculation of the number of available algorithms */
    int numberofalgorithms=sizeof(myalgorithms)/sizeof(SortAlgorithm);

    t_timevalue sortduration, sortdurationpresorted;
    t_timevalue measurement[5][14];
    t_timevalue measurementpresorted[5][14];

    for (int i=0; i<numberofalgorithms; i++)
    {
        printf("Testing %s:\n", algorithmname[i]);
        for(int y=0; y<numberofexperiments; y++)
        {
            measureAlgorithm(myalgorithms[i], experimentsize[y], &sortduration, &sortdurationpresorted);
            measurement[i][y] = sortduration;
            measurementpresorted[i][y] = sortdurationpresorted;
        }
    }




    printf("randomly generated list: \n");
    printf("Samples Bubblesort Shakersort Quicksort Selectionsort Insertionsort\n");
    for(int i=0; i<numberofexperiments; i++)
    {
        printf("%ld,", experimentsize[i]);
        for(int y=0; y<numberofalgorithms; y++)
        {
            printf("%15f,",measurement[y][i]/1000000.0);
        }
        printf("\n");

    }
    printf("\n");

    printf("presorted list: \n");
    printf("Samples Bubblesort Shakersort Quicksort Selectionsort Insertionsort\n");
    for(int i=0; i<numberofexperiments; i++)
    {
        printf("%ld,", experimentsize[i]);
        for(int y=0; y<numberofalgorithms; y++)
        {
            printf("%15f,",measurementpresorted[y][i]/1000000.0);
        }
        printf("\n");

    }

    return 0;
}

