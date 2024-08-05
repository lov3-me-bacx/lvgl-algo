#ifndef algo_homescreen_h
#define algo_homescreen_h

#include "lvgl/lvgl.h"

typedef struct{
    lv_obj_t *screen;
    int **dataset;
}HomeScreen;


HomeScreen create_home_screen();
void free_home_screen(HomeScreen screen);
#endif
