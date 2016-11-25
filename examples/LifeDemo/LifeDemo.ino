/*
File:   LifeDemo.ino
Author: J. Ian Lindsay
Date:   2016.11.24

License is attribution-only.


Simple sketch illustrating library usage.
*/


#include <Serial.h>
#include <ArduinoGOL.h>

/* Pin definitions */
const int PIN_LED = 6;  // Gives a visual indication of processing time.

/* Global objects */
ArduinoGOL<80, 25> gol;   // We allocate this way to keep all memory on-stack.


void showState() {
  uint16_t x = gol.sizeX();
  uint16_t y = gol.sizeY();
  char* buffer[x+1];  // We aggregate output in this buffer.
  for (uint16_t j = 0; j < y; j++) {
    for (uint16_t i = 0; i < x; i++) {
      buffer[i] = getCell(i, j) ? '*' : ' ';
    }
    buffer[x+1] = '\0';
    Serial.println(buffer);
  }
  Serial.println(' ');
}


void showGOLInfo() {
  Serial.print("Field area:        ");
  Serial.print(gol.sizeY());
  Serial.print(" rows by ");
  Serial.print(gol.sizeX());
  Serial.println(" columns");
  Serial.print("Memory footprint:  ");
  Serial.print(sizeof(gol));
  Serial.println(" bytes");
  Serial.print("Current GoL frame: ");
  Serial.println(gol.frame());
  Serial.println(' ');
}


/*******************************************************************************
* Main
*******************************************************************************/
void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("GoL demo ready.");
}


void loop() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'n':
        digitalWrite(PIN_LED, HIGH);
        gol.next();
        digitalWrite(PIN_LED, LOW);
        showState();
        break;
      case 'N':
        digitalWrite(PIN_LED, HIGH);
        gol.next(10);
        digitalWrite(PIN_LED, LOW);
        showState();
        break;
      case 'r':
        gol.randomize(0);
        showState();
        break;
      case 'i':
        showGOLInfo();
        break;
      case 'w':
        gol.wipe();
        // NOTE: No break;
      case 's':
        Serial.print("Current GoL frame: ");
        Serial.println(gol.frame());
        showState();
        break;
      default:
        Serial.println("Unrecognized");
        break;
    }
  }
}
