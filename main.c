#include "lvgl/lvgl.h"

#include "home_screen.h"
#include "bar_graph.h"

#include <unistd.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

static void hal_init(void) {
  lv_display_t *disp = lv_sdl_window_create(WIN_WIDTH, WIN_HEIGHT);

  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);
}

int main() {
  lv_init();

  hal_init();

  // sort_button();

  HomeScreen home_screen = create_home_screen();

  BarGraph *bar_screen = create_bar_graph_screen();
  lv_screen_load(bar_screen->screen);

  while (1) {
    lv_timer_handler();
    usleep(5000);
  }

  free_home_screen(home_screen);
  return 0;
}
