//
// Created by macbook on 16/03/2020.
//

#ifndef SUPEEPROM_POOL_H
#define SUPEEPROM_POOL_H

#include <Arduino.h>


class Pool {
public:
    static bool eLights;
    static bool eTimer;
    static bool eGrow;
    static bool eLight_1;
    static bool eLight_2;
    static bool eLight_3;
    static uint8_t sLTankMin;// = 4;
    static uint8_t sLTankMax;// = 6;
    static uint8_t sHTankMin;// = 4;
    static uint8_t sHTankMax;// = 36;
    static uint8_t eGrowTimeMin;
    static uint8_t eGrowTimeMax;
    static uint8_t eBloomTimeMin;
    static uint8_t eBloomTimeMax;
    static uint8_t eDrenageStop;
    static uint8_t eFillStop;
    static bool eSaveMode;
};


#endif //SUPEEPROM_POOL_H
