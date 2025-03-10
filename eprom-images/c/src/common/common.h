/*****************************************************/
/* Common functions that may be useful on the 65C02. */
/* Author: Sebastian Dawid                           */
/* E-Mail: sdawid@techfak.uni-bielefeld.de           */
/*****************************************************/

#include <stdint.h>

// The `bin_to_dec` function generates a decimal string of the given `number`.
// The user must provide a buffer to write the string into along with the buffers
// length. The return value of the function is the starting address of the written
// string. The number will be written into the buffer back to front. The length of
// the buffer includes the null terminator. This means the "29" is a string of length
// three.
uint8_t* bin_to_dec(const uint16_t number, uint8_t*const string, uint8_t length);
uint8_t* bin_to_hex(uint16_t number, uint8_t*const string, uint8_t length);
