//
// Helper functions for calculating colors/gradients/effects
//

uint32_t gradient(uint8_t progress, uint32_t from, uint32_t to) {
  return pixelsColor(
           map(progress, 0, 255, (uint8_t)(from >> 16), (uint8_t)(to >> 16)),
           map(progress, 0, 255, (uint8_t)(from >> 8), (uint8_t)(to >> 8)),
           map(progress, 0, 255, (uint8_t)(from), (uint8_t)(to))
         );
}

uint32_t gradient3(uint8_t progress, uint32_t from, uint32_t middle, uint32_t to) {
  if (progress < 128) {
    return gradient(progress * 2, from, middle);
  } else {
    return gradient((progress - 128) * 2, middle, to);
  }
}

uint8_t progress(uint32_t time, uint32_t duration, uint32_t offset) {
  return map((time + offset) % duration, 0, duration, 0, 255);
}

uint32_t gradientSlide(uint32_t time, uint32_t duration, uint32_t offset, uint32_t from, uint32_t to) {
  return gradient3(progress(time, duration, offset), from, to, from);
}

uint8_t timeOffset(uint32_t time, uint32_t speed, uint8_t pos, uint8_t count) {
  return ((time / speed) + pos) % count;
}

uint32_t colorSlide2(uint32_t time, uint32_t duration, uint8_t led, uint32_t c1, uint32_t c2) {
  uint8_t pos = timeOffset(time, duration, led, 2);
  return pos == 0 ? c1 : c2;
}

uint32_t colorSlide3(uint32_t time, uint32_t duration, uint8_t led, uint32_t c1, uint32_t c2, uint32_t c3) {
  uint8_t pos = timeOffset(time, duration, led, 3);
  return pos == 0 ? c1 : (pos == 1 ? c2 : c3);
}

uint32_t dropSlide(uint32_t time, uint32_t duration, uint8_t count, uint8_t led, uint32_t c) {
  uint8_t p = progress(time, duration, duration / count * led);
  if (p >= 255 / 3)
    return 0;
  else
    return gradient(p * 3, c, 0);
}



// some magic for defining mode functions

#define MODE_RETURN uint32_t
#define MODE_PARAMS (uint8_t led, uint32_t time)
#define MODE(__name) MODE_RETURN __name MODE_PARAMS
typedef MODE_RETURN (*ModeFunction) MODE_PARAMS;
MODE(autoswitch);

