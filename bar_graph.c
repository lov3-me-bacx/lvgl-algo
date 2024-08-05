#include "bar_graph.h"

#include "sorting.h"


#include "lvgl/src/misc/lv_event.h"
#include "lvgl/src/misc/lv_types.h"
#include "lvgl/src/widgets/chart/lv_chart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int data[20] =   {
        179, 167, 53,  10, 158, 126, 21,  150, 9,  59,
        27,  95,  102, 86, 46,  77,  191, 122, 89, 25,
    };
int data1[50]={
  403,152,449,215,445,558,518,546,171,422,
  386,64,567,289,426,431,416,146,313,572,555,
  245,50,545,549,213,437,553,503,249,346,586,
  105,557,563,491,599,220,202,498,448,323,481,
  169,108,77,393,399,537,356
};
void init_bar_graph(BarGraph *graph){
  graph->count = 0;
  graph->series = NULL;
  graph->values = NULL;
  graph->screen = NULL;
}

void free_bar_graph(BarGraph *graph){
  free(graph->values);
  init_bar_graph(graph);
}
static void swap_values(int *v1,int *v2,BarGraph *graph){
  int temp = *v1;
  *v1 = *v2;
  *v2 = temp;
  lv_chart_refresh(graph->chart);
  lv_refr_now(NULL);
  usleep(20000);
}

static void sort_event(lv_event_t *e){
  BarGraph *graph = (BarGraph*)lv_event_get_user_data(e);
  bubble_sort(lv_chart_get_y_array(graph->chart, graph->series),graph->count,swap_values,graph);
}
void add_sort_button(BarGraph *graph){

  lv_obj_t *label;

  lv_obj_t *btn = lv_button_create(graph->screen);
  lv_obj_add_event_cb(btn,sort_event,LV_EVENT_CLICKED,graph);
  lv_obj_align(btn,LV_ALIGN_TOP_MID,0,0);
  lv_obj_set_height(btn,LV_SIZE_CONTENT);

  label = lv_label_create(btn);
  lv_label_set_text(label,"SORT");
  lv_obj_center(label);
}
void add_bar_graph(BarGraph *graph){
  lv_obj_t *main_cont = lv_obj_create(graph->screen);
  lv_obj_set_size(main_cont, LV_SIZE_CONTENT,500);
  lv_obj_center(main_cont);

  lv_obj_t *wrapper = lv_obj_create(main_cont);
  lv_obj_remove_style_all(wrapper);
  lv_obj_set_size(wrapper, LV_SIZE_CONTENT, lv_pct(100));
  lv_obj_set_flex_flow(wrapper, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *chart = lv_chart_create(wrapper);
  lv_obj_set_width(chart,800);
  lv_obj_set_flex_grow(chart,1);
  lv_chart_set_type(chart,LV_CHART_TYPE_BAR);
  lv_chart_set_range(chart,LV_CHART_AXIS_PRIMARY_Y,0,1000);
  lv_chart_set_range(chart,LV_CHART_AXIS_SECONDARY_Y,0,1000);
  lv_chart_set_point_count(chart,graph->count);
  lv_obj_set_style_radius(chart,0,0);

  graph->chart = chart;

   lv_chart_series_t *ser1 = lv_chart_add_series(chart,lv_palette_lighten(LV_PALETTE_LIGHT_GREEN, 2),LV_CHART_AXIS_PRIMARY_Y);
  graph->series = ser1;

  for(int i=0;i<graph->count;i++){
    lv_chart_set_next_value(chart,ser1,graph->values[i]);
  }

  lv_chart_refresh(chart);
}

BarGraph* create_bar_graph_screen(){
  BarGraph *graph = malloc(sizeof(BarGraph));
  init_bar_graph(graph);
  lv_obj_t *screen = lv_obj_create(NULL);
  graph->screen = screen;
  int size = sizeof(data1)/sizeof(data1[0]);
  
  graph->values = malloc(sizeof(data1));
  memcpy(graph->values,&data1,sizeof(data1));
  graph->count = size;
  add_bar_graph(graph);
  add_sort_button(graph);
  return graph;
}
