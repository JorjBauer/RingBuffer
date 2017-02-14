This is a very simplistic, small, C++ Ring Buffer class.

It only understands bytes (uint8_t). You tell it what size FIFO you
want, in bytes on construction, like this 16-byte ring buffer:

  #include <RingBuffer.h>

  RingBuffer rb(16);

This class has no "thread-safe" (interrupt disabling) functionality,
by design. 

If you want to know why: I want to use this in code that counts time
via interrupts, and I can't have anything disabling interrupts or
they'll affect my timekeeping. So, I'm not wrapping code blocks in
ATOMIC_BLOCK (which disables GIE).

Which is probably fine for most general purpose applications.

This does mean that you should not use this code from any interrupt
routine. If you do, then it's on you to ensure you don't have
something in loop() which is trying to add or remove data from the
ring buffer while something in the interrupt is doing the same.

Methods:

  void clear();

clears all data from the buffer.

  bool isFull();

returns true if the buffer is full.

  bool hasData();

returns true if there is any data in the buffer.

  bool addByte(uint8_t b);

attempts to add one byte to the buffer. If the buffer is full, the
byte is not added and this method returns false; it returns true if
the byte is successfully added to the ring buffer.

  bool addBytes(uint8_t *b, int count);

attempts to add 'count' bytes to the buffer. If the buffer fills, 
processing stops and this method returns false. It returns true 
only if all of the bytes are successfully added to the ring buffer.

  uint8_t consumeByte();

returns one byte at the head of the buffer, and removes it from the
buffer. (Returns 0 if there are no bytes in the buffer; check
hasData() first.)

  uint8_t peek(int idx);

Returns the byte at index <idx> of the buffer, if there is one. Note
that this does not test whether or not there are enough bytes in the
buffer to satisfy this request - the data returned may be stale! Be
sure to check count() first.

  int count();

Returns the number of bytes currently in the buffer.
