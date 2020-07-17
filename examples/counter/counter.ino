/*
 * This example demonstrates a simple countdown
 */

// Include the interfacing library
#include "segm8.h"

// Let's declare 1 module using hardware SPI with CS on 10 pin
SegM8 module(10, 1);

int counter = 9;

void setup() {
  // initialise SegM8
  module.begin();

  // Display "StArt"
  module.display("s", 0, 1);
  delay(1000);
  module.display("t", 0, 1);
  delay(1000);
  module.display("a", 0, 1);
  delay(1000);
  module.display("r", 0, 1);
  delay(1000);
  module.display("t", 0, 1);
  delay(1000);
}

void loop() {
  if (counter < 0)
    counter = 9;

  // display countdown
  module.display(counter--, 0, 1);

  delay(1000);
}
