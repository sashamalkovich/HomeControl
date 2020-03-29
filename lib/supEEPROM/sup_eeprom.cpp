#include "sup_eeprom.h"

SupEEPROM::SupEEPROM() {
    eDefPut();
};

SupEEPROM::~SupEEPROM() = default;

Pool SupEEPROM::pool;

void SupEEPROM::ePut() {
    EEPROM.put(0, pool);

}

void SupEEPROM::eGet() {
    EEPROM.get(0, pool);
}

void SupEEPROM::eDefPut() {
    Pool::eBloomTimeMax = 20;
    Pool::eBloomTimeMin = 8;
    Pool::eDrenageStop = 24;
    Pool::eFillStop = 8;
    Pool::eGrow = false;
    Pool::eGrowTimeMax = 22;
    Pool::eGrowTimeMin = 6;
    Pool::eLight_1 = true;
    Pool::eLight_2 = true;
    Pool::eLight_3 = true;
    Pool::eLights = true;
    Pool::eSaveMode = false;
    Pool::eTimer = true;
    Pool::sHTankMax = 36;
    Pool::sHTankMin = 4;
    Pool::sLTankMax = 6;
    Pool::sLTankMin = 4;

}
