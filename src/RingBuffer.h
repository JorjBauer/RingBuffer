#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

#include <Arduino.h>

class RingBuffer {
 public:
  RingBuffer(int length);
  ~RingBuffer();

  void clear();

  bool isFull();
  bool hasData();
  bool addByte(byte b);
  byte consumeByte();
  byte peek(int idx);
  int count();
  
 private:
  byte *buffer;
  int max;
  int ptr;
  int fill;
};

#endif
