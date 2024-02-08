# pico_macropad
demo of macropad for pico using shopee philippines 3 key, rgb led, encoder

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


