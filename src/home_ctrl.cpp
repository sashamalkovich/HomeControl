#include "home_ctrl.h"

HomeCtrl::HomeCtrl(){

    pSrArray = new int[2];
    pinMode(LED_BUILTIN, HIGH);


}

HomeCtrl::~HomeCtrl() = default;

void HomeCtrl::setup(){
    setupFunc();
}

void HomeCtrl::run() {

    exec();
   /*
    pSrArray = go();
    if (pSrArray[0] == 0 && pSrArray[1] == 1) {
        digitalWrite(LED_BUILTIN, HIGH);
        pLcd->setCursor(0, 0);
        pLcd->print("ON");
    } else if ((pSrArray[0] == 0 && pSrArray[1] == 0)) {
        digitalWrite(LED_BUILTIN, LOW);
        pLcd->setCursor(0, 0);
        pLcd->print("OFF");
        

    }
    */
}



