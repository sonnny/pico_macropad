#include "hardware/pio.h"
#include "encoder.pio.h"

PIO pio_1 = pio1;
const uint sm1 = 0;

void encoder_init(){
  pio_add_program(pio1,&encoder_program);
  encoder_program_init(pio_1,sm1,6,0);
}

int encoder_count(){
  return encoder_get_count(pio_1,sm1);}
