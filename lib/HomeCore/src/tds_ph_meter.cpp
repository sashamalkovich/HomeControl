#include "tds_ph_meter.h"


TdsPhMeter::TdsPhMeter() {

    phArray = new int[SCOUNT];
    tdsArray = new int[SCOUNT];



}

TdsPhMeter::~TdsPhMeter() {

    delete[] phArray;
    delete[] tdsArray;

}

void TdsPhMeter::tdsPhSetup() {

    pinMode(PH_PIN, INPUT);
    pinMode(TDS_PIN, INPUT);

}

double TdsPhMeter::getPH() {

    static unsigned long timer = millis();
    static int iter = 0;
    uint32_t rawVoltage = 0;
    static float voltage = 0.0;
    static float phValue = 0.0;

    if(millis() - timer > 40U) {
        timer = millis();
        phArray[iter] = analogRead(PH_PIN);
        for (int i = 0; i < SCOUNT -1; i++)
        {
            for (int j = i + 1; j < SCOUNT; j++)
            {
                if (phArray[i] > phArray[j])
                {
                    phTemp = phArray[i];
                    phArray[i] = phArray[j];
                    phArray[j] = phTemp;
                }
            }
        }
        for (int i = 0; i < SCOUNT; i++) {
            rawVoltage  += phArray[i];
        }

        voltage = rawVoltage  / SCOUNT * (float) 5.0 / 1024.0;;

        iter++;
        iter > SCOUNT ? iter = 0 : iter = iter;
    }

    phValue = -5.70 * voltage + phCalibration;

    return phValue;
}

double TdsPhMeter::getTDS(float temperature) {
    static unsigned long timer = millis();
    static int iter = 0;
    uint32_t rawVoltage = 0;
    static float voltage = 0.0;
    static float tdsValue = 0.0;

if(millis() - timer > 40U) {
    timer = millis();
    tdsArray[iter] = analogRead(TDS_PIN);

    for (int i = 0; i < SCOUNT; i++) {
        rawVoltage  += tdsArray[i];
    }

    voltage = rawVoltage  / SCOUNT * (float) 5.0 / 1024.0;;

    iter++;
    iter > SCOUNT ? iter = 0 : iter = iter;
}
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVolatge = voltage / compensationCoefficient;
    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5;

    return tdsValue *2;
}
