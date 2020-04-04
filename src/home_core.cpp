#include "home_core.h"

HomeCore::HomeCore()
{
    pLcd = new LiquidCrystal_I2C(0x27, 20, 4);
    pOneWire = new OneWire(ONE_WIRE_BUS);
    pSensor = new DallasTemperature(pOneWire);
    pTemp = new int[2];
    pSS = new int[2];
    pTime = new iarduino_RTC(RTC_DS3231);
    timeArray = new int[4];
    knobON = new bool[6];
    paramArray = new int *[7];
    count = 0;
    actualcount = 0;
    state = 0;
    pinAValue = 0;
    pinBValue = 0;
    zero = 0;
    for (int i = 0; i < 6; i++)
    {
        knobON[i] = false;
    }
    for (int i = 0; i < 7; i++)
    {
        for (int y = 0; y < 7; y++)
        {
            paramArray[i][y] = zero;
        }
    }
}

HomeCore::~HomeCore() = default;

void HomeCore::setupCore()
{
    pLcd->init();
    pLcd->backlight();
    pSensor->begin();
    //pTime->begin();
    _setup();
}

int *HomeCore::getTemp()
{
    pSensor->requestTemperatures();
    pTemp[0] = (int)((pSensor->getTempC(sensor1)) + 0.51);
    pTemp[1] = (int)((pSensor->getTempC(sensor2)) + 0.51);
    return pTemp;
}

int HomeCore::superSonic(uint8_t PIN_IN, uint8_t PIN_OUT)
{
    unsigned long dur;
    unsigned int cm;
    digitalWrite(PIN_OUT, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_OUT, HIGH);
    delayMicroseconds(20);
    digitalWrite(PIN_OUT, LOW);
    dur = pulseIn(PIN_IN, HIGH, 200);
    cm = dur / 29 / 2;
    return cm;
}

int *HomeCore::getSS()
{
    pSS[0] = superSonic(SS_PIN_IN_0, SS_PIN_OUT_0);
    pSS[1] = superSonic(SS_PIN_IN_1, SS_PIN_OUT_1);
    return pSS;
}

int *HomeCore::getTime()
{
    pTime->gettime();
    timeArray[0] = pTime->Hours;
    timeArray[1] = pTime->minutes;
    timeArray[2] = pTime->seconds;
    timeArray[3] = pTime->day;
    return timeArray;
}

uint8_t HomeCore::encoder()
{
    pinAValue = digitalRead(ENCODER_PIN_0); // Получаем состояние пинов A и B
    pinBValue = digitalRead(ENCODER_PIN_1);
    cli(); // Запрещаем обработку прерываний, чтобы не отвлекаться
    if (!pinAValue && pinBValue)
        state = 1; // Если при спаде линии А на линии B лог. единица, то вращение в одну сторону
    if (!pinAValue && !pinBValue)
        state = -1; // Если при спаде линии А на линии B лог. ноль, то вращение в другую сторону
    if (pinAValue && state != 0)
    {
        if (state == 1 && !pinBValue || state == -1 && pinBValue)
        { // Если на линии А снова единица, фиксируем шаг
            count += state;
            state = 0;
        }
    }
    sei(); // Разрешаем обработку прерываний
    return count;
}

bool HomeCore::knob2state(uint8_t knob)
{
    static bool switch_enc = false;
    bool state;
    state = digitalRead(knob);
    while (!state)
    {
        state = digitalRead(knob);

        switch_enc = true;
    }
    if (state && switch_enc)
    {
        switch_enc = false;
        state = true;
    }
    else if (state && !switch_enc)
    {
        state = false;
    }

    return state;
}

int **HomeCore::runCore()
{
    paramArray[0] = getTemp();
    paramArray[1] = getSS();
    paramArray[2] = getTime();
   // /* 
    paramArray[3][1] = bool2int(knob2state(KNOB_0));
    paramArray[3][2] = bool2int(knob2state(KNOB_1));
    paramArray[3][3] = bool2int(knob2state(KNOB_2));
    paramArray[3][4] = bool2int(knob2state(SAVE_KNOB_PIN));
    paramArray[3][5] = bool2int(knob2state(ESCAPE_KNOB_PIN));
    paramArray[3][6] = bool2int(knob2state(ENCODER_KNOB));
    paramArray[4][0] = encoder();
      //  */

    return paramArray;
}

int HomeCore::bool2int(bool in)
{
    if (in)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
