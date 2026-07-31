#pragma once
#include "config.h"

inline void touchWriteBits(uint8_t data, int bits) {
  for (int i = bits - 1; i >= 0; i--) {
    digitalWrite(TOUCH_DIN, (data >> i) & 0x01);
    delayMicroseconds(1);
    digitalWrite(TOUCH_CLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(TOUCH_CLK, LOW);
    delayMicroseconds(1);
  }
}

inline uint16_t touchRead12(uint8_t command) {
  uint16_t value = 0;

  digitalWrite(TOUCH_CS, LOW);
  delayMicroseconds(5);
  touchWriteBits(command, 8);

  for (int i = 0; i < 12; i++) {
    digitalWrite(TOUCH_CLK, HIGH);
    delayMicroseconds(1);

    value <<= 1;
    if (digitalRead(TOUCH_OUT)) value |= 1;

    digitalWrite(TOUCH_CLK, LOW);
    delayMicroseconds(1);
  }

  digitalWrite(TOUCH_CS, HIGH);
  delayMicroseconds(5);
  return value;
}

inline uint16_t readTouchX() { return touchRead12(0xD0); }
inline uint16_t readTouchY() { return touchRead12(0x90); }

inline bool isTouchPressed(uint16_t rawX, uint16_t rawY) {
  return (abs((int)rawX - idleX) > touchThresholdX) ||
         (abs((int)rawY - idleY) > touchThresholdY);
}

inline int rawToScreenX(uint16_t rawY) {
  int x = map(rawY, rawYLeft, rawYRight, 20, 459);
  return constrain(x, 0, 479);
}

inline int rawToScreenY(uint16_t rawX) {
  int y = map(rawX, rawXTop, rawXBottom, 20, 299);
  return constrain(y, 0, 319);
}

inline bool pointInRect(int px, int py, const RectButton& b) {
  return (px >= b.x && px < b.x + b.w && py >= b.y && py < b.y + b.h);
}

inline bool pointInArrow(int px, int py, const ArrowButton& b) {
  return (px >= b.x && px < b.x + b.w && py >= b.y && py < b.y + b.h);
}