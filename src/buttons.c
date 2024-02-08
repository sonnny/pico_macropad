#include <buttons.h>
#include "hardware/gpio.h"
#include <stdbool.h>

void buttons_init(){
  gpio_init(10); gpio_set_dir(10,GPIO_IN); gpio_pull_up(10);
  gpio_init(11); gpio_set_dir(11,GPIO_IN); gpio_pull_up(11);
  gpio_init(12); gpio_set_dir(12,GPIO_IN); gpio_pull_up(12);}
  
uint8_t buttonRead(){
  if (!gpio_get(10)) return 1;
  else if (!gpio_get(11)) return 2;
  else if (!gpio_get(12)) return 3;
  else return 0;}
