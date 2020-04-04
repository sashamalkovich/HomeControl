#ifndef _HOME_CTRL_H_
#define _HOME_CTRL_H_


#include "Menu.h"
#include "Functions.h"
#include <Wire.h>


class HomeCtrl : public Functions {
public:

    explicit HomeCtrl();

    ~HomeCtrl();

    void run();

    void setup();

private:


    int *pSrArray;
   // LiquidCrystal_I2C *pLcd;


};

#endif //_HOME_CTRL_H_
