#include "segm8.h"

SegM8 module(10, 1);
int counter = 9;

void setup() {
  module.begin();
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
  module.display(counter--, 0, 1);

  delay(1000);
}
