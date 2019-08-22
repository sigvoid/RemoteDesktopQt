#ifndef MOUSEARRAY_H
#define MOUSEARRAY_H
#include <stdlib.h>
#include <stdint.h>
using namespace std;

const uint8_t mouse_map[] = {
  /*Pixel format: Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0xff, 0xdb, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xb7, 0x00, 0x00, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x49, 0x00, 0x49, 0x00, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0x6d, 0x00, 0x24, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0x6e, 0x00, 0x24, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0x92, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xb6, 0x00, 0x00, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x00, 0x00, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x24, 0x00, 0x6e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x24, 0x00, 0x6e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0x00, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x49, 0x00, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6d, 0x00, 0x24, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6e, 0x00, 0x24, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0x00, 0x00, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0x24, 0x00, 0xdb,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xdb, 0xb7, 0x6d, 0x00, 0x6e,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdb,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0xff, 0xff, 0xdb, 0x24, 0x24, 0x25, 0x49, 0x6d, 0x92, 0x92, 0xdb, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0xff, 0x49, 0x00, 0xff, 0xff, 0xff, 0x6d, 0x00, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0xff, 0x49, 0x00, 0x24, 0x6d, 0xff, 0xff, 0xff, 0x00, 0x24, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xff, 0xff, 0x24, 0x00, 0x49, 0x25, 0x24, 0xff, 0xff, 0xff, 0x6d, 0x00, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0xdb, 0x24, 0x00, 0x49, 0xff, 0x6d, 0x00, 0x92, 0xff, 0xff, 0xdb, 0x00, 0x49, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x6d, 0x00, 0x24, 0x00, 0x92, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x49, 0x00, 0xdb, 0xff, 0xff, 0xff, 0xff,
  0xff, 0x49, 0x24, 0x92, 0xff, 0xff, 0xff, 0xff, 0x25, 0x00, 0x92, 0xff, 0xff, 0xdb, 0x00, 0x25, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0x00, 0x25, 0xff, 0xff, 0xff, 0x49, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x25, 0x00, 0xb7, 0xff, 0xff, 0x6d, 0x00, 0x92, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x92, 0x00, 0x49, 0x6d, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x49, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xdb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
#endif // MOUSEARRAY_H