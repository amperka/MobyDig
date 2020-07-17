/*
 * This example demonstrates the outline of the available symbols on a SegM8 module.
 * Unavailable characters are displayed as underscore.
 */

// Include the interfacing library
#include "segm8.h"

// Let's declare 1 module using hardware SPI with CS on 10 pin
SegM8 module(10, 1);

int counter = 0;
char symbol[2] = " ";

void setup() {
    // initialise SegM8
    module.begin();
}

void loop() {
    if (counter > 63)
        counter = 0;

    // convert the character number to its code
    symbol[0] = (' ' + counter++);
    // display character
    module.display(symbol, 0, 1);
    
    delay(700);
}
