cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "/home/sonny/pico/pico-sdk")

include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

project(template C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_library(template
  src/ws2812.c
  src/buttons.c
  src/hid_keys.c
  src/ssd1306.c
  src/encoder.c
  src/usb_descriptors.c)

target_include_directories(template PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include )
target_include_directories(template PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src )

pico_generate_pio_header(template ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio)
pico_generate_pio_header(template ${CMAKE_CURRENT_LIST_DIR}/src/encoder.pio)

target_link_libraries(template
  hardware_gpio
  hardware_pio
  hardware_i2c
  tinyusb_device
  tinyusb_board
  pico_stdlib)
