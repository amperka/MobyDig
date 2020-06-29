#include "segm8.h"

SegM8 module(10,1);
int counter = 10;

void setup() {
  module.begin();
  module.display("s",0,1);
  delay(1000);
  module.display("t",0,1);
  delay(1000);
  module.display("a",0,1);
  delay(1000);
  module.display("r",0,1);
  delay(1000);
  module.display("t",0,1);
  delay(1000);    
}

void loop() {
  module.clear();
  if(counter >= 0)
    module.display(counter--,0,1);
  delay(1000);
}
