#include "RingBuffer.h"
#include <stdlib.h>

RingBuffer::RingBuffer(int16_t length)
{
  this->buffer = (uint8_t *)malloc(length);
  this->max = length;
  this->fill = 0;
  this->ptr = 0;
  this->cursor = 0;
}

RingBuffer::~RingBuffer()
{
  free (this->buffer);
}

void RingBuffer::clear()
{
  this->fill = 0;
}

bool RingBuffer::isFull()
{
  return (this->max == this->fill);
}

bool RingBuffer::hasData()
{
  return (this->fill != 0);
}

bool RingBuffer::addByte(uint8_t b)
{
  if (this->max == this->fill)
    return false;

  int idx = (this->ptr + this->fill) % this->max;
  this->buffer[idx] = b;
  this->fill++;
  return true;
}

bool RingBuffer::replaceByte(uint8_t b)
{
  if (cursor < fill) {
    buffer[cursor] = b;
    cursor++;
    if (cursor >= fill) {
      cursor = 0;
    }
    return true;
  }
  return false;
}


bool RingBuffer::addBytes(uint8_t *b, int count)
{
  for (int i=0; i<count; i++) {
    if (!addByte(b[i]))
      return false;
  }
  return true;
}

uint8_t RingBuffer::consumeByte()
{
  if (this->fill == 0)
    return 0;
  
  uint8_t ret = this->buffer[this->ptr];
  this->fill--;
  this->ptr++;
  this->ptr %= this->max;
  return ret;
}

uint8_t RingBuffer::peek(int16_t idx)
{
  uint16_t p = (this->ptr + idx) % this->max;
  return this->buffer[p];
}

int16_t RingBuffer::count()
{
  return this->fill;
}

uint16_t RingBuffer::Cursor()
{
  return this->cursor;
}

void RingBuffer::setPeekCursor(int16_t idx)
{
  this->cursor = idx;
}

void RingBuffer::resetPeekCursor()
{
  this->cursor = 0;
}

uint8_t RingBuffer::peekNext()
{
  uint8_t ret = peek(cursor);
  cursor++;
  if (cursor >= fill) {
    cursor = 0;
  }
  return ret;
}
