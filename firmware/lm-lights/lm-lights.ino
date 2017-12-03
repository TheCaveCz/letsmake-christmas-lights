//
//  Christmas Lights
//  part of Let's make series
//
//  The Cave, 2017
//  https://thecave.cz
//
//  Licensed under MIT License (see LICENSE file for details)
//
//  This sketch supports several user defined modes for determining colors
//  of led strip. You can cycle through modes by pressing a button. If you
//  hold button longer, you will reverse the animations.
//
//  Check x20_modes tab, where you can easily add new modes for your LEDs.
//  Each mode function gets called for each LED and is expected to return
//  a color of that specific LED. You will also get time parameter that
//  indicates number of milliseconds since the mode was selected.
//  

#define PIN_BUTTON 7
#define PIN_BUTTON_GND 6
#define PIN_PIXELS 3

// How long (milliseconds) will autoswitch keep one mode
#define MODE_AUTOSWITCH_TIME 5000UL

