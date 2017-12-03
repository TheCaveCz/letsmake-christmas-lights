//
//  Here you can write your own mode functions
//  Do not forget to put them in the list at the bottom!
//

MODE(m1) {
  return gradientSlide(time, 2000, (4000 / PIXELS_COUNT) * led, 0xff0000, 0x0000ff);
}

MODE(m2) {
  return gradientSlide(time, 5000, (5000 / PIXELS_COUNT) * led, 0xff0000, 0xff00);
}

MODE(m3) {
  return colorSlide3(time, 80, led, 0xff00, 0xff0000, 0xff);
}

MODE(m4) {
  return colorSlide2(time, 500, led, 0xffff00, 0x00ffff);
}

MODE(m5) {
  return gradientSlide(time, 4000, 1000 * led, 0x800000, 0x808000);
}

MODE(m6) {
  return dropSlide(time, 1000, 25, led, 0xffffff);
}



ModeFunction modes[] = {
  autoswitch, // if the autoswitch mode is included, it must be first!!

  // put all the functions for modes here!
  m6,
  m5,
  m4,
  m3,
  m2,
  m1,


  NULL // you need to keep the NULL here
};

