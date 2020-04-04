//#include <Arduino.h>
#include "sup_eeprom.h"

class A : public SupEEPROM {
public:
    void run();

};

void A::run() {
    //eDefPut();
    //ePut();
    eGet();
    Serial.println(Pool::eLights);
    Serial.println(Pool::eGrowTimeMax);

}

A a;

void setup() {
    Serial.begin(9600);
    a.run();


}

void loop() {

}
