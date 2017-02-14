#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

#include <stdint.h>

class RingBuffer {
 public:
  RingBuffer(int16_t length);
  ~RingBuffer();

  void clear();

  bool isFull();
  bool hasData();
  bool addByte(uint8_t b);
  bool addBytes(uint8_t *b, int count);
  bool replaceByte(uint8_t b);
  uint8_t consumeByte();
  uint8_t peek(int16_t idx);
  void setPeekCursor(int16_t idx);
  void resetPeekCursor();
  uint8_t peekNext();
  int16_t count();
  uint16_t Cursor();

 private:
  uint8_t *buffer;
  int16_t max;
  int16_t ptr;
  int16_t fill;
  int16_t cursor;
};

#endif
