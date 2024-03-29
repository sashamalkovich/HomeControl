#ifndef _HOME_CORE_H_
#define _HOME_CORE_H_

#include <iarduino_RTC.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include "coreSetup.h"
#include "dataBase.h"
#include "tds_ph_meter.h"

class HomeCore : TdsPhMeter
{

public:
    explicit HomeCore();

    ~HomeCore();

    LiquidCrystal_I2C *pLcd;

protected:
    DataBase db;
    int *pTemp;
    int *pSS;
    int *timeArray;
    bool *knobON;
    iarduino_RTC *pTime;
    OneWire *pOneWire;
    DallasTemperature *pSensor;
    DeviceAddress sensor1 = {0x28, 0x20, 0x83, 0x03, 0x00, 0x00, 0x80, 0x29};
    DeviceAddress sensor2 = {0x28, 0xFF, 0xA8, 0xD9, 0x61, 0x15, 0x01, 0x94};

    bool lights;
    bool light_0;
    bool light_1;
    bool light_2;
    uint8_t drainON;
    bool drenage;
    static bool saveMode;
    bool timerOnOff;
    uint8_t fillStop;
    uint8_t drenageStop;
    uint8_t GrowTimeMax;
    uint8_t GrowTimeMin;
    uint8_t BloomTimeMax;
    uint8_t BloomTimeMin;
    uint8_t DrenageStop;
    uint8_t FillStop;
    uint8_t Grow;
    uint8_t sHTankMax;
    uint8_t sHTankMin;
    uint8_t sLTankMin;
    uint8_t sLTankMax;

    uint8_t oHourStart;
    uint8_t oMinuteStart;
    uint8_t oMinuteLenght;
    uint8_t oDays_Every;
    
    struct acidFert
    {
       uint8_t acidTimerHour;
       uint8_t acidTimerMin;
       uint8_t acidTimerDuration;
    };

    acidFert acidf;
    
    void acidFlow();

    bool oOnOff;

    bool drFeedback;

    float phTds[2] = {0, 0};

    virtual void setupCore();

    virtual int *getTemp();

    virtual int *getSS();

    virtual int *getTime();

    virtual uint8_t encoder();

    static bool knob2state(uint8_t);

    virtual int **runCore();

    virtual void sendIter();

    virtual void saveParam();

    bool drenageOnOff();

    void save();

    static void (*resetFunc)(void);

    unsigned int waterCycleGet();

    uint16_t wateringCycleGet();

    void wateringCycleAdd();

    void waterCycleAdd();

    void waterWatering(uint8_t, uint8_t, uint8_t);

    virtual void lcdOnOff();

    virtual void lcdOnOff(bool);

private:
    int **paramArray;
    int actualcount; // Временная переменная определяющая изменение основного счетчика
    volatile int count;
    volatile int state;     // Переменная хранящая статус вращения
    volatile int pinAValue; // Переменные хранящие состояние пина, для экономии времени
    volatile int pinBValue;

    unsigned int waterCycles;

    uint16_t wateringCount;

    void drenageFUNC();

    void waterLevel(uint8_t);

    void waterLevelHT(uint8_t);

    virtual void escape();

    static int superSonic(uint8_t, uint8_t);

    static int bool2int(bool);

    static int *knobArray();

    void lightsTimer();

    void tempLighsOff();

    void watering(uint8_t _hour, uint8_t _minutes, uint8_t _day);

    void drenageStopFunc();

    void drain();

    void fill();

    void fillHt();

    void drainHt();
};

#endif //_HOME_CORE_H_
