#include <Arduino.h>
#include "home_ctrl.h"

char sym = '~';

HomeCtrl homeCtrl;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    Serial2.begin(115200);
    homeCtrl.setup();

}

void loop()
{
    homeCtrl.run();
}
