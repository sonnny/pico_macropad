
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

//we only have 3 leds on the board
uint32_t leds[3] = {0,0,0};
PIO pio=pio0;
int sm=0;
uint offset;
  
void ws2812_test(uint32_t color){
  //if i used for loop it doesn't work
  //but if a specify 3 pio_sm_put_blocking statement then it works
  pio_sm_put_blocking(pio0,0,color<<8u);
  pio_sm_put_blocking(pio0,0,color<<8u);
  pio_sm_put_blocking(pio0,0,color<<8u);}
  

void ws2812_init(){
  offset=pio_add_program(pio,&ws2812_program);
  ws2812_program_init(pio,sm,offset,13,800000,false);	
  //blank leds
  ws2812_test(0x00000000);}
  
void ws2812_set_color(uint8_t num, uint32_t color){
  leds[0]=0; leds[1]=0; leds[2]=0;
  //switch keys
  switch(num){
	case 0: leds[2]=color; break;
	case 1: leds[1]=color; break;
	case 2: leds[0]=color; break;}
  pio_sm_put_blocking(pio0,0,leds[0]<<8u);
  pio_sm_put_blocking(pio0,0,leds[1]<<8u);
  pio_sm_put_blocking(pio0,0,leds[2]<<8u);}
  

	
