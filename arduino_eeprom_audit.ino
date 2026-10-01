#include <Arduino.h>
#include "EEPROMAudit.h"

void setup() {
    Serial.begin(9600);
    while (!Serial);
    delay(1000);

    runFullActiveAudit();
}

void loop() {

}