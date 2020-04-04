#ifndef _HOME_CORE_H_
#define _HOME_CORE_H_

#include <iarduino_RTC.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <ser_res.h>
#include "coreSetup.h"

class HomeCore : public SerRes
{

public:
    explicit HomeCore();

    ~HomeCore();

    LiquidCrystal_I2C *pLcd;

protected:
    int *pTemp;
    int *pSS;
    int *timeArray;
    bool *knobON;
    iarduino_RTC *pTime;

    OneWire *pOneWire;
    DallasTemperature *pSensor;
    DeviceAddress sensor1 = {0x28, 0x20, 0x83, 0x03, 0x00, 0x00, 0x80, 0x29};
    DeviceAddress sensor2 = {0x28, 0xFF, 0xA8, 0xD9, 0x61, 0x15, 0x01, 0x94};

    virtual void setupCore();

    virtual int *getTemp();

    virtual int *getSS();

    virtual int *getTime();

    virtual uint8_t encoder();

    virtual bool knob2state(uint8_t);

    virtual int **runCore();

private:
    int **paramArray;
    int actualcount; // Временная переменная определяющая изменение основного счетчика
    volatile int count;
    volatile int state;     // Переменная хранящая статус вращения
    volatile int pinAValue; // Переменные хранящие состояние пина, для экономии времени
    volatile int pinBValue;
    int zero;

    static int superSonic(uint8_t, uint8_t);

    static int bool2int(bool);
};

#endif //_HOME_CORE_H_
