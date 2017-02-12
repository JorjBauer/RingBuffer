#include <RingBuffer.h>

RingBuffer::RingBuffer(int length)
{
  this->buffer = (byte *)malloc(length);
  this->max = length;
  this->fill = 0;
  this->ptr = 0;
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

bool RingBuffer::addByte(byte b)
{
  if (this->max == this->fill)
    return false;

  int idx = (this->ptr + this->fill) % this->max;
  this->buffer[idx] = b;
  this->fill++;
  return true;
}

bool RingBuffer::addBytes(byte *b, int count)
{
  for (int i=0; i<count; i++) {
    if (!addByte(b[i]))
      return false;
  }
  return true;
}

byte RingBuffer::consumeByte()
{
  if (this->fill == 0)
    return 0;
  
  byte ret = this->buffer[this->ptr];
  this->fill--;
  this->ptr++;
  this->ptr %= this->max;
  return ret;
}

byte RingBuffer::peek(int idx)
{
  int p = (this->ptr + idx) % this->max;
  return this->buffer[p];
}

int RingBuffer::count()
{
  return this->fill;
}
