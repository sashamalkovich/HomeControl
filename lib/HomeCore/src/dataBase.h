#include <Arduino.h>

struct DataBase
{
    bool eLights;
    bool eTimer;
    bool eGrow;
    bool eLight_1;
    bool eLight_2;
    bool eLight_3;
    uint8_t sLTankMin; // = 4;
    uint8_t sLTankMax; // = 6;
    uint8_t sHTankMin; // = 4;
    uint8_t sHTankMax; // = 36;
    uint8_t eGrowTimeMin;
    uint8_t eGrowTimeMax;
    uint8_t eBloomTimeMin;
    uint8_t eBloomTimeMax;
    uint8_t eDrenageStop;
    uint8_t eFillStop;
    bool eSaveMode;
    uint8_t oHourStart;
    uint8_t oMinuteStart;
    uint8_t oMinuteLenght;
    bool oOnOff;
};
