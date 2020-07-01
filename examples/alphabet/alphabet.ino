#include "segm8.h"

SegM8 module(10, 1);
int counter = 64;
char* symbol = " ";

void setup() {
    module.begin();
}

void loop() {
    if (counter > 63)
        counter = 0;
    symbol[0] = (' ' + counter++);
    module.display(symbol, 0, 1);
    delay(700);
}