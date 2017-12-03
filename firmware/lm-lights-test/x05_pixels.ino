/*
  Parts of this code are taken from Adafruit NeoPixel library.

----------------------------------------------------------------------------
  Arduino library to control a wide variety of WS2811- and WS2812-based RGB
  LED devices such as Adafruit FLORA RGB Smart Pixels and NeoPixel strips.
  Currently handles 400 and 800 KHz bitstreams on 8, 12 and 16 MHz ATmega
  MCUs, with LEDs wired for various color orders.  Handles most output pins
  (possible exception with upper PORT registers on the Arduino Mega).

  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries,
  contributions by PJRC, Michael Miller and other members of the open
  source community.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  NeoPixel is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NeoPixel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

 */
 
#define PIXELS_BYTES PIXELS_COUNT*3


uint8_t pixels[PIXELS_BYTES];
uint32_t pixelsEndTime;
volatile uint8_t *pixelsPort;
uint8_t pixelsPinMask;


void pixelsBegin() {
  pixelsEndTime = 0;

  pixelsPort = portOutputRegister(digitalPinToPort(PIN_PIXELS));
  pixelsPinMask = digitalPinToBitMask(PIN_PIXELS);

  pinMode(PIN_PIXELS, OUTPUT);
  digitalWrite(PIN_PIXELS, LOW);
}

void pixelsSetColor(uint16_t n, uint32_t c) {
  if (n >= PIXELS_COUNT) return;

  uint8_t *p;
  p = &pixels[n * 3];
  p[0] = (uint8_t)(c >> 16);
  p[1] = (uint8_t)(c >>  8);
  p[2] = (uint8_t)c;
}

uint32_t pixelsColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void pixelsShow(void) {
  while ((micros() - pixelsEndTime) < 300L);

  volatile uint16_t i = PIXELS_BYTES; // Loop counter
  volatile uint8_t *ptr = pixels,   // Pointer to next byte
                    b   = *ptr++,   // Current byte value
                    hi,             // PORT w/output bit set high
                    lo;             // PORT w/output bit set low

  noInterrupts();

  volatile uint8_t next, bit;

  hi   = *pixelsPort |  pixelsPinMask;
  lo   = *pixelsPort & ~pixelsPinMask;
  next = lo;
  bit  = 8;

  asm volatile(
    "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
    "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
    "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
    "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
    "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
    "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
    "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
    "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
    "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
    "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
    "nop"                      "\n\t" // 1    nop           (T = 13)
    "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
    "nop"                      "\n\t" // 1    nop           (T = 16)
    "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
    "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
    "nextbyte20:"               "\n\t" //                    (T = 10)
    "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
    "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
    "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
    "nop"                      "\n\t" // 1    nop           (T = 16)
    "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
    "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
    : [port]  "+e" (pixelsPort),
    [byte]  "+r" (b),
    [bit]   "+r" (bit),
    [next]  "+r" (next),
    [count] "+w" (i)
    : [ptr]    "e" (ptr),
    [hi]     "r" (hi),
    [lo]     "r" (lo));

  interrupts();
  pixelsEndTime = micros();
}

