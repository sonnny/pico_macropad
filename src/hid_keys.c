#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp/board.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "tusb.h"

#include "buttons.h"
#include "usb_descriptors.h"
#include "mapping.h"

void hid_task(uint8_t k, uint8_t t);

void hid_keys_init(){
    board_init();
    tusb_init();}

void tud_mount_cb(void){}

void tud_umount_cb(void){}

void tud_suspend_cb(bool remote_wakeup_en){
    (void)remote_wakeup_en;}

void tud_resume_cb(void){}

#define NUM_SIMULTANEOUS_USB_KEY_CODES 6

bool addKey(uint8_t existingKeycodes[NUM_SIMULTANEOUS_USB_KEY_CODES], uint8_t newKeyCode){

    for (int idx = 0; idx < NUM_SIMULTANEOUS_USB_KEY_CODES; idx++){
        if (existingKeycodes[idx] == 0){
            existingKeycodes[idx] = newKeyCode;
            return true;}}

    // All slots full so could not add this new keycode
    return false;}

void hid_task(uint8_t k, uint8_t t){
  static uint8_t prevSentKeycodes[6] = {0};
  uint8_t keycodes[6] = {0};
  int dummy;
  
  switch(t){
    case VOLUME: switch(k){//volume controls, taken from hid codes
			           case 0: keycodes[0] = 0x00; break;
	               case 1: keycodes[0] = 0x80; break; //volume up
	               case 2: keycodes[0] = 0x7f; break; //mute
	               case 3: keycodes[0] = 0x81; break; //volume down
	             } break;
	             
    case COPY_PASTE: switch(k){//cut paste code taken from hid codes
		                      //assumes mouse highlighted what needs to be copy and paste
		                case 0: keycodes[0] = 0x00; break;
	                  case 1: keycodes[0] = 0xe0; keycodes[1] = 0x06; break; //control c
	                  case 2: keycodes[0] = 0x7c; break;
	                  case 3: keycodes[0] = 0xe0; keycodes[1] = 0x19; break; //control v
	                } break;
	                
    case CAPITAL: switch(k){
			            case 0: keycodes[0]=0x00; keycodes[1]=0x00; break; //release
			            case 1: keycodes[0]=0xe1; keycodes[1]=0x04; break; //left shift + a
			            case 2: keycodes[0]=0xe1; keycodes[1]=0x05; break; //left shift + b
			            case 3: keycodes[0]=0xe1; keycodes[1]=0x06; break; //left shift + c
								} break;
    
    case SMALL: switch(k){
			
							} break;
	                                      	             	           
  }

    // Check if any new key codes need to be send
    bool newKeysToSend = false;
    for (int idx = 0; idx < 6; idx++){
        if (keycodes[idx] != prevSentKeycodes[idx]){
            newKeysToSend = true;
            prevSentKeycodes[idx] = keycodes[idx];}}

    if (newKeysToSend){
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycodes);}
    
    bypass:
    dummy=0;
    
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen){
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;}

// Invoked when received SET_REPORT control request or received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize){
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;}
