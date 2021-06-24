#ifndef _TDS_PH_METER_H_
#define _TDS_PH_METER_H_

#include <Arduino.h>
#include "def.h"

class TdsPhMeter {

public:
    explicit TdsPhMeter();
    ~TdsPhMeter();

protected:

    void tdsPhSetup();

    double getPH();

    double getTDS(float);

private:

    int *phArray;
    int phTemp;
    int *tdsArray;

    float phCalibration = 27.0; //ph calibration Value;


};

#endif //_TDS_PH_METER_H_
