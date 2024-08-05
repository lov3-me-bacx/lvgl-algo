#include "home_screen.h"
#include "lvgl/src/layouts/flex/lv_flex.h"
#include "lvgl/src/misc/lv_area.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const static int data_sample[3][20] = {
    {
        179, 167, 53,  10, 158, 126, 21,  150, 9,  59,
        27,  95,  102, 86, 46,  77,  191, 122, 89, 25,
    },
    {
        97,  109, 298, 229, 253, 72,  133, 51,  193, 159,
        260, 233, 165, 147, 111, 145, 180, 128, 226, 244,
    },
    {
        99,  161, 117, 130, 157, 98,  134, 159, 96,  111,
        199, 195, 193, 175, 113, 118, 142, 121, 115, 127,
    }};

static void init_home_screen(HomeScreen screen) {
  screen.screen = NULL;
  screen.dataset = NULL;
}

static void show_title(lv_obj_t *disp) {
  lv_obj_t *label = lv_label_create(disp);
  lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_label_set_text(label, "Choose a data set");
}
static void add_dataset(const int arr[], int length,lv_obj_t *parent) {
  lv_obj_t *label = lv_label_create(parent);
  
  char text[200];
  int index = 0;
  for (int i = 0; i < length; i++) {
    index +=sprintf(&text[index],"%d , ",arr[i]);
  }
  printf("%s \n",text);
lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
lv_label_set_text(label,text);
  printf("-------------------------------END-------------------------------- \n");
}
static void show_main_cont(HomeScreen home_screen) {

  lv_obj_t *main_cont;
  main_cont = lv_obj_create(home_screen.screen);
  lv_obj_set_size(main_cont, lv_pct(100), lv_pct(100));
  lv_obj_set_flex_flow(main_cont, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(main_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  show_title(main_cont);

 for (int i = 0; i < 3; i++) {
      add_dataset(data_sample[i],20,main_cont);
  }
}

HomeScreen create_home_screen() {
  HomeScreen home_screen;
  init_home_screen(home_screen);
  home_screen.screen = lv_obj_create(NULL);
  home_screen.dataset = malloc(sizeof(data_sample));
  memcpy(home_screen.dataset,&data_sample,sizeof(data_sample));
  show_main_cont(home_screen);
  return home_screen;
}

void free_home_screen(HomeScreen screen) {
  free(screen.screen);
  free(screen.dataset);
}
