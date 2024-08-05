#include "sorting.h"






void bubble_sort(int *arr,int n, swp_fn swp,BarGraph *graph){
  int i,j;
  bool swapped;
  for(i = 0; i < n - 1;i++){
    swapped = false;
    for (j = 0; j < n - i - 1; j++){
      if (arr[j] > arr[j + 1]){
        swp(&arr[j],&arr[j+1],graph);
        swapped = true;
      }
    }
    if (!swapped){
      break;
    }
  }
}


