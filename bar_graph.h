#ifndef algo_bar_h
#define algo_bar_h

#include "lvgl/lvgl.h"


typedef struct{
    int count;
    int *values;
    lv_chart_series_t *series;
    lv_obj_t *chart;
    lv_obj_t *screen;
}BarGraph;

void init_bar_graph(BarGraph *graph);
void free_bar_graph(BarGraph *graph);


void bar_graph_screen(BarGraph *graph);
BarGraph* create_bar_graph_screen();
#endif
