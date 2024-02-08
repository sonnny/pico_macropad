
#ifndef _HID_KEYS_H_
#define _HID_KEYS_H_

#include <stdint.h>
#include "tusb.h"
#include "bsp/board.h"

void tud_task();
void hid_task(uint8_t k, uint8_t t);
void hid_keys_init();


#endif // _BUTTONS_H_
