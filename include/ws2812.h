#ifndef __WS2812_H__
#define __WS2812_H__

void ws2812_init();
void ws2812_set_color(uint8_t num, uint32_t color);
void ws2812_test(uint32_t color);

#endif
