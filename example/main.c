

// macropad demo
// hardware found on shopee philippines
//    1 encoder with middle button
//    3 keys with rgb led
//
// hid keys modified from https://github.com/PhilboBaggins/pico-keys
// ws2812 from pico examples
// encoder from pico examples
// ssd1306 from pico examples
//
// volume mapping demo shows how to send one key press to computer

// cut paste mapping demo shows how to send two keys to hid
//    first key in the array is control
//    second key in the array is 'C' or 'V'

// capital mapping demo shows how to send two keys to hid
//    first key in the array is left shift
//    second key in the array is 'a' or 'b' or 'c'
//
// for every pressed key/s you have to send released keys (all zeros in the 6 byte array)


#include "pico/stdlib.h"
#include "hid_keys.h"
#include "ws2812.h"
#include "ssd1306.h"
#include "encoder.h"
#include "mapping.h"

uint8_t new_key=0;
uint8_t old_key=0;
int new_encoder_value = 0;
int old_encoder_value = 0;
uint8_t map_type = 0;
char str[64];

int main(void){
   gpio_init(8); gpio_set_dir(8,GPIO_IN); gpio_pull_up(8);  
   hid_keys_init();
   ssd1306_init();
   ws2812_init();
   encoder_init();
   buttons_init();
   sleep_ms(100);
   ws2812_test(0xffffffff); // light up all leds white
   WriteString(0,20,"TESTING...");
   sleep_ms(3000);
   ws2812_test(0x00000000); // turn off leds
   WriteString(0,20,"VOLUME");
   sleep_ms(100);
  
   for(;;){

  	 tud_task();
	   new_key = buttonRead();
	   
	   if (new_key != old_key) {
			 hid_task(new_key, map_type);
			 old_key = new_key;}
			 
		 if (new_key > 0) ws2812_set_color(new_key - 1, 0x00ffff00);

    //change mode
		new_encoder_value = encoder_count();
		
		if (new_encoder_value > (old_encoder_value + 8)){//check if its clockwise
		  map_type += 1;
		  if (map_type > MAX_TYPE - 1) map_type = 0;
		  old_encoder_value = new_encoder_value;
		  ssd1306_update(map_type);}
		  
		sleep_ms(10);////// adjust this for debounce
  }

    return 0;
}

