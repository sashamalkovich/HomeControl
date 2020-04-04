#ifndef _SUP_EEPROM_H_
#define _SUP_EEPROM_H_

#include <EEPROM.h>
#include "Pool.h"



class SupEEPROM: public Pool {

public:
    explicit SupEEPROM();

    ~SupEEPROM();


    static Pool pool;

protected:
    static void ePut();

    static void eGet();

    static void eDefPut();


};

#endif //_SUP_EEPROM_H_
