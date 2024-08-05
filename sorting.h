#ifndef algo_sorting_h
#define algo_sorting_h

#include "bar_graph.h"

typedef void (*swp_fn)(int*,int*,BarGraph*);
void bubble_sort(int *arr,int n,swp_fn swp,BarGraph *graph);

#endif

