/*
 * Simplistic ring buffer example: a 500mS serial echo delay
 *
 * (c) 2016 Jorj Bauer <jorj@jorj.org>
 * 
 * This code is released under the MIT license. See License.txt for
 * details.
 */

#include <RingBuffer.h>

RingBuffer rb(128);

void setup() {
  Serial.begin(115200);
}

void loop() {
  static unsigned long delayUntil = 0;
  
  while (Serial.available() > 0) {
    if (!rb.addByte(Serial.read())) {
      Serial.write("Overflow!\n");
    }
    delayUntil = millis() + 500;
  }

  if (millis() >= delayUntil) {
    while (rb.hasData()) {
      Serial.write(rb.consumeByte());
    }
  }
}
